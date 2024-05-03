
#include <cxxopts.hpp>
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>
#include <sofa/core/ComponentLibrary.h>

#include <sofa/helper/logging/Messaging.h>
#include <sofa/helper/system/FileSystem.h>

#include <sofa/simulation/config.h>
#include <sofa/simulation/Node.h>

#include <sofa/helper/logging/LoggingMessageHandler.h>

#include <sofa/core/ObjectFactory.h>
#include <sofa/helper/BackTrace.h>
#include <sofa/helper/system/FileRepository.h>
#include <sofa/helper/system/PluginManager.h>
#include <sofa/simulation/graph/DAGNode.h>
#include <sofa/simulation/graph/init.h>

struct FileContent
{
    std::string directory;
    std::string content;
};

void loadPlugins(const char* const appName, const std::vector<std::string>& pluginsToLoad);

void generateDoc(const std::string& output);

int main(int argc, char** argv)
{
    constexpr const char* appName = "PluginFinder";
    cxxopts::Options options(appName, "Generate SOFA documentation based on the ObjectFactory");
    options.add_options()
        ("verbose", "Verbose")
        ("h,help", "print usage")
        ("l,load", "load given plugins", cxxopts::value<std::vector<std::string>>())
        ("o,output", "Documentation is generated in this directory", cxxopts::value<std::string>());

    const auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    sofa::helper::logging::MessageDispatcher::addHandler(&sofa::helper::logging::MainLoggingMessageHandler::getInstance());
    sofa::helper::logging::MainLoggingMessageHandler::getInstance().activate();

    sofa::helper::BackTrace::autodump();
    sofa::simulation::graph::init();

    std::vector<std::string> pluginsToLoad;
    if (result.count("load"))
    {
        pluginsToLoad = result["load"].as<std::vector<std::string>>();
    }
    loadPlugins(appName, pluginsToLoad);

    std::map<std::string, std::string > aliases; //key: alias, value: original name
    sofa::core::ObjectFactory::getInstance()->setCallback([&aliases](sofa::core::Base* o, sofa::core::objectmodel::BaseObjectDescription *arg)
    {
        const std::string typeNameInScene = arg->getAttribute("type", "");
        if ( typeNameInScene != o->getClassName() )
        {
            aliases[typeNameInScene] = o->getClassName();
        }
    });

    const auto verbose = result["verbose"].as<bool>();

    generateDoc(result["output"].as<std::string>());

    sofa::simulation::graph::cleanup();
    return 0;
}

void loadPlugins(const char* const appName, const std::vector<std::string>& pluginsToLoad)
{
    for (const auto& plugin : pluginsToLoad)
    {
        sofa::helper::system::PluginManager::getInstance().loadPlugin(plugin);
    }

    std::string configPluginPath = "plugin_list.conf";
    std::string defaultConfigPluginPath = "plugin_list.conf.default";
    if (sofa::helper::system::PluginRepository.findFile(configPluginPath, "", nullptr))
    {
        msg_info(appName) << "Loading automatically plugin list in " << configPluginPath;
        sofa::helper::system::PluginManager::getInstance().readFromIniFile(configPluginPath);
    }
    else if (sofa::helper::system::PluginRepository.findFile(defaultConfigPluginPath, "", nullptr))
    {
        msg_info(appName) << "Loading automatically plugin list in " << defaultConfigPluginPath;
        sofa::helper::system::PluginManager::getInstance().readFromIniFile(defaultConfigPluginPath);
    }
    else
    {
        msg_info(appName) << "No plugin list found. No plugin will be automatically loaded.";
    }
}

void generateComponentDoc(
    const std::string& outputDirectory,
    std::unordered_map<std::string, FileContent>& fileContent,
    const sofa::core::ClassEntry::SPtr& entry,
    sofa::core::ObjectFactory::Creator::SPtr creator,
    std::mutex& mutex)
{
    auto targetDirectory = std::string{creator->getTarget()};

    // replace . by /
    std::replace( targetDirectory.begin(), targetDirectory.end(), '.', '/');

    std::string directory = sofa::helper::system::FileSystem::append(outputDirectory, targetDirectory);
    directory = sofa::helper::system::FileSystem::convertBackSlashesToSlashes(directory);

    const std::string filename = sofa::helper::system::FileSystem::append(directory, entry->className + ".md");

    auto it = fileContent.find(filename);
    if (it == fileContent.end())
    {
        FileContent content;
        content.content = "# " + entry->className + "\n\n";

        content.content += entry->description + "\n\n";

        content.directory = directory;
        std::lock_guard guard(mutex);
        it = fileContent.insert({filename, content}).first;
    }

    if (!creator->getClass()->templateName.empty())
    {
        it->second.content += "## " + creator->getClass()->templateName + "\n\n";
    }

    it->second.content += "__Target__: " + std::string{creator->getTarget()} + "\n\n";
    it->second.content += "__namespace__: " + creator->getClass()->namespaceName + "\n\n";
    if (!creator->getClass()->parents.empty())
    {
        it->second.content += "__parents__: \n";

        for (const auto& parent : creator->getClass()->parents)
        {
            it->second.content += "- " + parent->className + "\n";
        }
        it->second.content += "\n";
    }

    const auto tmpNode = sofa::core::objectmodel::New<sofa::simulation::graph::DAGNode>("tmp");
    if (tmpNode)
    {
        sofa::core::objectmodel::BaseObjectDescription desc;
        const auto object = creator->createInstance(tmpNode.get(), &desc);
        if (object)
        {
            it->second.content += "Data: \n\n";

            it->second.content += "| Name | Description | Default value |\n";
            it->second.content += "| ---- | ----------- | ------------- |\n";
            for (const auto& data : object->getDataFields())
            {
                if (data)
                {
                    it->second.content +=
                        "| " + data->getName() +
                        " | " + data->getHelp() +
                        " | " + data->getDefaultValueString() + " |\n";
                }
            }
        }
    }
}

void generateDoc(const std::string& output)
{
    static std::vector<sofa::core::ClassEntry::SPtr> entries;
    sofa::core::ObjectFactory::getInstance()->getAllEntries(entries);

    std::unordered_map<std::string, FileContent> fileContent;

    std::vector<std::thread> threads;
    std::mutex mutex;

    threads.reserve(entries.size());
    for (const auto& entry : entries)
    {
        std::cout << entry->className << std::endl;
        threads.emplace_back([&entry, &output, &fileContent, &mutex]()
        {
            for (const auto& [templateInstance, creator] : entry->creatorMap)
            {
                generateComponentDoc(output, fileContent, entry, creator, mutex);
            }
        });
    }

    for (auto& t : threads)
    {
        t.join();
    }

    for (const auto& [filename, content] : fileContent)
    {
        sofa::helper::system::FileSystem::findOrCreateAValidPath(content.directory);
        std::ofstream f(filename);
        f << content.content;
    }
}

# SOFA Components Documentation

Welcome to the comprehensive documentation of SOFA, featuring an organized inventory of all its components alongside select plugins.
This documentation is complementary to the official documentation website: [sofa-framework.org/community/doc](https://www.sofa-framework.org/community/doc/)

[![SOFA, Simulation Open-Framework Architecture](https://www.sofa-framework.org/wp-content/uploads/2013/01/SOFA_LOGO_ORANGE_2-normal.png)](https://www.sofa-framework.org/)

## Overview
In this repository, you will discover detailed descriptions of each component, along with any associated templates. Each component entry includes a breakdown of available templates and their respective data, accompanied by thorough descriptions.

## Navigation
To explore the documentation efficiently, use the following structure:

__Components__: Browse through a curated list of all SOFA components.

__Templates__: Access specific templates associated with each component, providing insight into available data and functionalities.

__Data Overview__: Gain a comprehensive understanding of the data offered within each template, facilitating informed utilization of SOFA components.

## How to Use
__Component Exploration__: Select a component from the list to delve into its details, including available templates and associated data.
__Template Selection__: Choose a template to view its data composition and functionalities, enabling seamless integration into your projects.
__Data Analysis__: Evaluate the data within each template to determine its relevance and applicability to your specific requirements.

## How it Works

The documentation and its website are generated automatically, based on the SOFA binaries, using GitHub actions following the pipeline:

1. Setup SOFA and environment
2. Build the application. The application depends on SOFA and extract documentation from the ObjectFactory in SOFA.
3. Markdown generation
4. Build docs using Writerside Docker builder
5. Deploy

# brepviewer
An incomplete BREP [Boundary REPresentation](https://en.wikipedia.org/wiki/Boundary_representation) viewer written in CPP using OpenGL.

## Feature Roadmap
- [] Lua scripting to dynamically update Vertex and Model data
- [] BREP model loading
- [] BREP triangulation algo's
- [] Render BREP models

## Style Guide
### Naming Conventions
- **Global Variables** use: *gALL_CAPS*
- **Macros** use: *ALL_CAPS*
- **Non-Member Functions** use: *PascalCase()* 
- **Local Variables & Struct Member Variables** use: *snake_case*
- **Structs, Classes, & Namespaces** use: *PascalCase*
- **Class Member Variables** use: *m_snake_case*
- **Class Methods** use: *dromedaryCase()*

### Glossary
- **size**: size measured in some underlying type (i.e. int)
- **stride**: size in bytes
- **count**: current count of items in an array
- **capacity**: the max amount of items an array can hold

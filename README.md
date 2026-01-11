# brepviewer
An incomplete BREP [Boundary REPresentation](https://en.wikipedia.org/wiki/Boundary_representation) viewer written in CPP using OpenGL.

## Feature Roadmap
- [] Lua scripting to dynamically update Vertex and Model data
- [] BREP model loading
- [] BREP triangulation algo's
- [] Render BREP models

## C++ Style Guide
### Naming Conventions
- **Macros** use: **ALL_CAPS**
- **Global Variables** use: **gALL_CAPS**
- **Local Variables** use: **snake_case**
- **Non-Member Functions** use: **PascalCase()** or **identifier_PascalCase()**
- **Namespaces** use: **snake_case** (prefer single word or acronym, i.e. "brep"; abbreviate if necessary)
- **Structs, Classes, & Enums** use: **PascalCase**
- **Private & Protected Member Variables** use: **m_snake_case**
- **Public Member Variables** use: **snake_case**
- **Methods** use: **dromedaryCase()**
- Notes:
  - Capitalize acronyms, i.e. brep -> BREP

### Glossary
- **size**: current size in bytes
- **capacity**: total capacity measured in bytes
- **stride**: offset in bytes between consecutive elements
- **offset**: generic memory offset measured in bytes
- **count**: current count of items in an array
- **length**: the number of (available) indices in an array

### Preferred Abbreviations & Acronyms
- *attribs* = *attributes*
- *coords* = *coordinates*

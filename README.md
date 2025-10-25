# Cabinet Loader Tool

A tool to help with loading cabinets and furniture into vans for a carpentry business.

## Project Structure

```
src/
├── main.c              # Main application entry point
├── core/               # Core business logic
│   ├── van.{c,h}       # Van data structure and operations
│   ├── cabinet.{c,h}   # Cabinet data structure and operations
│   └── loader.{c,h}    # Load plan management
├── data_structs/       # Data structures
│   ├── list.{c,h}      # Linked list for cabinets
│   └── vector.{c,h}    # Dynamic array (future use)
├── algorithms/         # Packing algorithms
│   └── packing.{c,h}   # Various packing strategies
├── io/                 # Input/output operations
│   ├── input.{c,h}     # Interactive input functions
│   └── file_io.{c,h}   # File operations (future use)
└── utils/              # Utility functions
    ├── helpers.{c,h}   # General helper functions
    └── config.{c,h}    # Configuration management
```

## Testing

Build and run the validation tests with:

```
make loader_validate_tests
./loader_validate_tests
```

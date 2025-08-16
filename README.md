# ScienceFiction Library 🚀📚

A comprehensive digital library management system for science fiction content, developed as an Object-Oriented Programming university project at the Department of Mathematics, University of Padova.

## 👥 Authors
- **Lorenzo Soligo** - 2101057
- **Antonio Tang** - 2111017

*Report by Lorenzo Soligo*

## 📖 Project Overview

The ScienceFiction Library is a specialized digital content management system designed for science fiction enthusiasts. Users can manage a diverse collection of sci-fi content including books, comics, films, TV series, and video games with an intuitive and flexible interface.

### 🎯 Key Features
- **Multi-format Content Management**: Books, Comics, Films, TV Series, Video Games
- **Import/Export**: Support for XML and JSON formats
- **Advanced Filtering**: Granular search with multiple parameter combinations
- **Visual Status Indicators**: Color-coded frames for watched/starred content
- **Keyboard Shortcuts**: Complete keyboard navigation support
- **Persistent Data**: Automatic save state management

## 🌟 Visual Design

The interface uses a color-coding system for instant content recognition:
- **🟢 Neon Green**: Watched content
- **🟡 Fluorescent Yellow**: Starred/Favorite content  
- **🟣 Neon Purple**: Both watched AND starred content  \

Here what the main window looks like:
  <img width="1852" height="1020" alt="image" src="https://github.com/user-attachments/assets/31a97939-4331-435e-8f1e-0a3c0de2cfc9" />


## 🏗️ Architecture & Design Patterns

### Class Hierarchy
```
Content (Abstract Base Class)
├── Paper (Abstract)
│   ├── Book
│   └── Comic
└── Multimedia (Abstract)
    ├── Video (Abstract)
    │   ├── Film
    │   └── Serie
    └── VideoGame
```

### Design Patterns Implemented
- **Visitor Pattern**: Dynamic GUI rendering and data persistence
- **Singleton Pattern**: Single library instance management
- **Bitmask Pattern**: Efficient subgenre representation

## 🧬 Core Components

### Content Management
Every content item includes:
- **Unique ID**: For relationship tracking (inspiration, prequel/sequel)
- **Subgenres**: Bitmask implementation for multiple sci-fi subgenres
- **Metadata**: Title, publication year, status flags
- **Relationships**: Inspiration links, prequel/sequel chains

### Subgenre System
Advanced bitmask implementation allowing:
- Multiple subgenre assignment per content
- Efficient storage and retrieval
- Granular filtering capabilities
- String representation for display

## 🖥️ User Interface

### Main Features
- **Content Cards**: Visual grid with cover images and status indicators
- **Detail View**: Comprehensive information display using Visitor pattern
- **Edit Mode**: Type-specific editing forms
- **Advanced Filtering**: Multi-parameter search with live results
- **Responsive Layout**: Automatic adaptation to screen size

### Navigation
Complete keyboard shortcut support for power users:

| Shortcut | Action |
|----------|--------|
| **Main Window** |  |
| `Ctrl+N` | Create new content |
| `Ctrl+I` | Import library |
| `Ctrl+S` | Save as JSON |
| `Ctrl+Shift+S` | Save as XML |
| `Ctrl+F` | Toggle filters |
| `Ctrl+Shift+F` | Clear all filters |
| `Ctrl+K` | Focus search bar |
| `F5` | Refresh view |
| `Ctrl+D` | Change sort direction |
| **Detail/Edit Windows** |  |
| `Esc` | Close window |
| `Ctrl+S` | Save changes |
| `Ctrl+Z` | Undo changes |

## 💾 Data Persistence

### Supported Formats
- **XML**: Qt-based serialization with type tags
- **JSON**: Structured export with error handling and content grouping

### Auto-Save Features
- **Unsaved Changes Detection**: Warns before closing with unsaved data
- **Import/Export Safety**: Prevents data loss during operations
- **File Validation**: Error handling for corrupted files

## 🔧 Technical Implementation

### Polymorphism Usage
The Visitor pattern enables:
- **Dynamic UI Generation**: Type-specific detail and edit views
- **Serialization**: Format-specific export (XML/JSON)
- **Extensibility**: Easy addition of new content types

### Memory Management
- **Smart Pointers**: `unique_ptr` usage for safety
- **Singleton Library**: Single instance with controlled access
- **Relationship Integrity**: Automatic cleanup of broken references

## 📊 Development Statistics

### Time Investment (Lorenzo Soligo)
| Activity | Planned Hours | Actual Hours |
|----------|---------------|--------------|
| Design & Planning | 15 | 15 |
| Model Development | 20 | 20 |
| GUI Development | 10 | 25 |
| Filter & Search | 10 | 15 |
| UX & Styling | 0 | 5-10 |
| Testing & Debug | 10 | 15 |
| Code Review | 5 | 5 |
| **Total** | **70** | **95-100** |

### Task Distribution

#### Lorenzo Soligo
- **Logic Model**: Content hierarchy (excluding VideoGame)
- **XML Persistence**: Complete serialization system
- **Main Interface**: Primary window and functionality
- **Search System**: Advanced filtering and search
- **UI/UX**: Icons, graphics, keyboard shortcuts

#### Antonio Tang
- **Logic Model**: Video hierarchy including VideoGame
- **JSON Persistence**: Complete serialization system  
- **Detail Views**: Dynamic content-specific interfaces
- **Edit System**: Type-aware editing functionality

## 🚀 Getting Started

### Prerequisites
- Qt Framework
- C++ Compiler with C++11+ support
- CMake (recommended)

### Installation
```bash
git clone https://github.com/Solgio/OOProject
cd OOProject
qmake
make
./OOProject
```

### Usage
1. **Launch Application**: Run the compiled executable
2. **Create Content**: Use `Ctrl+N` or the + button
3. **Import Library**: Load existing XML/JSON files
4. **Filter & Search**: Use the advanced filtering system
5. **Export**: Save your library in preferred format

## 📈 Quality Assurance

- **Static Analysis**: SonarQube integration for code quality
- **GitHub Integration**: Version control and collaboration
- **Modular Design**: Easy testing and maintenance
- **Error Handling**: Comprehensive validation and recovery

## 🔮 Future Enhancements

### Planned Features
- **Direct Deletion**: Remove content from main view
- **Library Merging**: Combine multiple libraries
- **Content Type Conversion**: Change content types dynamically  
- **Theme Support**: Light/Dark mode toggle
- **Batch Operations**: Multi-select actions

### Extensibility
The modular architecture supports:
- New content types without modifying existing code
- Additional export formats
- Custom filtering parameters
- Enhanced relationship types

## 📱 System Requirements

### Recommended
- **Resolution**: 1920x1080 for optimal experience
- **OS**: Cross-platform Qt support
- **Memory**: Adequate for large libraries
- **Storage**: Variable based on content collection

## 🏆 Academic Context

Developed for the Object-Oriented Programming course at the University of Padova, this project demonstrates:
- **OOP Principles**: Inheritance, polymorphism, encapsulation
- **Design Patterns**: Visitor, Singleton, proper abstraction
- **GUI Development**: Qt framework mastery
- **Software Engineering**: Version control, code quality, documentation

## 📄 Documentation

Complete project documentation available in Italian, including:
- UML class diagrams
- Design pattern explanations
- Implementation details
- Time tracking and task distribution

---

*This project showcases advanced object-oriented design principles applied to a real-world content management scenario, with emphasis on extensibility, user experience, and code quality.*

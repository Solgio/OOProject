# ScienceFiction_Library

Content library that implements the principles of **OOP**.\
The specification for this projects are described in the LateX file but here there is a summary of the most significant ones:
- Information Hiding
- Clear separation between *Logical Model* and *GUI*
- Non trivial *Polymorphism* implementation (NO Getters or GetType)
- Classes Hierarchy
- Data Persistency (*XML, JSON*)
## GUI
The GUI is created with the **Qt** library.
It's a simple, very essential Graphic Interaface that focus on **Usability** rather then eye-catching impact and for this reason could be improved.
It offers:
- Filtering options 
- Diversified view for different kind of Content
- Intuitive Buttons
- Easy to read icons
- Action Shortcut:
  
  |**Shortcut**      | **Azione**                |
  |--------------|-----------------------|
  | **MAIN WINDOW**                          |
  |  CTRL+N      | New content           |
  | CTRL+I       | Import library        |
  | CTRL+S       | Save library in Json  |
  | CTRL+SHIFT+S | Save library in Xml   |
  | CTRL+F       | Toggle filtering menu |
  | CTRL+SHIFT+F |Clean filter options   |
  | CTRL+K       | Focus on searchbar    |
  | F5           | Reload view           |
  | CTRL+D       | Change sort direction |
  |          **DETAIL e EDIT WINDOW**       |
  | ESC          | Close current page    |
  | CTRL+S       | Save edit of Content  |
  | CTRL+Z       | UN-ndo changes        |
  
- Unsaved changes alert when trying to close the application
- Basic Adaptive window behaviour
## Logic Model
The class hierarchy is as it follows:\
CONTENT* \
        ===> Paper*\
                                ===>Book\
                                              ===> Comic\
        ===> Multimedia*\
                                                                ===> Video*\
                                                                                     ===> Film\
                                                                                        ===> Serie\
                                              ===> VideoGame\
 "*" indicates an abstract class
- Use of Bitmask for Subgenre of Content, so that a content can have multiplle Subgenres. Bitmask chosen for better use of resources
- Singleton pattern for unique instance of ScienceFiction_Library
  
  
[![wakatime](https://wakatime.com/badge/user/732d1158-e701-4381-9bb0-df5f6f08b1c0/project/83e7d8a2-a677-400c-85e6-6e1c33e5931a.svg)](https://wakatime.com/badge/user/732d1158-e701-4381-9bb0-df5f6f08b1c0/project/83e7d8a2-a677-400c-85e6-6e1c33e5931a)

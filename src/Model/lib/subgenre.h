  enum class subGenre{
    Fantasy=0,
    Horror=1<<0,
    Mystery=1<<1,
    Thriller, Romance, Drama, Comedy, Action, Adventure, Documentary, Biography,
    History, Western, War, Crime, Musical, Animation, Family, Sports, Superhero
};

//!! BITMASK



#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <unordered_map>
#include <stdexcept>

// Define the subgenre flags as bits in an enum
enum Subgenre {
    NONE = 0,
    ACTION = 1 << 0,
    COMEDY = 1 << 1,
    DRAMA = 1 << 2,
    HORROR = 1 << 3,
    SCI_FI = 1 << 4,
    ROMANCE = 1 << 5,
    THRILLER = 1 << 6,
    DOCUMENTARY = 1 << 7,
    FANTASY = 1 << 8,
    ANIMATION = 1 << 9,
    // Add more subgenres as needed (up to 64 for 64-bit systems)
};

// Overload bitwise OR operator to combine subgenres
inline Subgenre operator|(Subgenre a, Subgenre b) {
    return static_cast<Subgenre>(static_cast<int>(a) | static_cast<int>(b));
}

// Content class representing a single content item
class Content {
public:
    Content(const std::string& title, const std::string& description, Subgenre subgenres)
        : title(title), description(description), subgenres(subgenres) {}

    // Check if content has a specific subgenre
    bool hasSubgenre(Subgenre genre) const {
        return (subgenres & genre) == genre;
    }

    // Check if content has any of the given subgenres
    bool hasAnySubgenre(Subgenre genres) const {
        return (subgenres & genres) != 0;
    }

    // Add a subgenre to this content
    void addSubgenre(Subgenre genre) {
        subgenres = subgenres | genre;
    }

    // Remove a subgenre from this content
    void removeSubgenre(Subgenre genre) {
        subgenres = static_cast<Subgenre>(subgenres & ~genre);
    }

    // Getters
    const std::string& getTitle() const { return title; }
    const std::string& getDescription() const { return description; }
    Subgenre getSubgenres() const { return subgenres; }

    // Convert subgenres to a readable string
    std::string getSubgenreString() const {
        std::string result;
        if (subgenres == NONE) return "None";

        if (hasSubgenre(ACTION)) result += "Action, ";
        if (hasSubgenre(COMEDY)) result += "Comedy, ";
        if (hasSubgenre(DRAMA)) result += "Drama, ";
        if (hasSubgenre(HORROR)) result += "Horror, ";
        if (hasSubgenre(SCI_FI)) result += "Sci-Fi, ";
        if (hasSubgenre(ROMANCE)) result += "Romance, ";
        if (hasSubgenre(THRILLER)) result += "Thriller, ";
        if (hasSubgenre(DOCUMENTARY)) result += "Documentary, ";
        if (hasSubgenre(FANTASY)) result += "Fantasy, ";
        if (hasSubgenre(ANIMATION)) result += "Animation, ";

        // Remove trailing comma and space
        if (!result.empty()) {
            result.erase(result.size() - 2);
        }

        return result;
    }

private:
    std::string title;
    std::string description;
    Subgenre subgenres;
};

// Content Library class to manage all content
class ContentLibrary {
public:
    // Add content to the library
    void addContent(const Content& content) {
        contents.push_back(content);
    }

    // Find content by title (case sensitive)
    Content* findContent(const std::string& title) {
        for (auto& content : contents) {
            if (content.getTitle() == title) {
                return &content;
            }
        }
        return nullptr;
    }

    // Get all content with specific subgenre(s)
    std::vector<Content*> getContentBySubgenre(Subgenre genre) {
        std::vector<Content*> result;
        for (auto& content : contents) {
            if (content.hasAnySubgenre(genre)) {
                result.push_back(&content);
            }
        }
        return result;
    }

    // Get all content
    const std::vector<Content>& getAllContent() const {
        return contents;
    }

private:
    std::vector<Content> contents;
};

// Helper function to print content details
void printContent(const Content& content) {
    std::cout << "Title: " << content.getTitle() << "\n";
    std::cout << "Description: " << content.getDescription() << "\n";
    std::cout << "Subgenres: " << content.getSubgenreString() << "\n";
    std::cout << "----------------------------\n";
}

int main() {
    // Create a content library
    ContentLibrary library;

    // Add some content with subgenres
    library.addContent(Content("The Matrix", "A computer hacker learns about the true nature of reality", 
                              SCI_FI | ACTION));
    library.addContent(Content("Inception", "A thief who steals corporate secrets through dream-sharing technology",
                              SCI_FI | ACTION | THRILLER));
    library.addContent(Content("The Shawshank Redemption", "Two imprisoned men bond over a number of years",
                              DRAMA));
    library.addContent(Content("Toy Story", "A cowboy doll is threatened by a new spaceman figure",
                              ANIMATION | COMEDY | FANTASY));

    // Find content by subgenre
    std::cout << "All Sci-Fi content:\n";
    auto sciFiContent = library.getContentBySubgenre(SCI_FI);
    for (auto content : sciFiContent) {
        printContent(*content);
    }

    // Find specific content
    std::cout << "\nSearching for 'Inception':\n";
    auto inception = library.findContent("Inception");
    if (inception) {
        printContent(*inception);
        
        // Check if it's a thriller
        if (inception->hasSubgenre(THRILLER)) {
            std::cout << "This is a thriller!\n";
        }
    }

    return 0;
}
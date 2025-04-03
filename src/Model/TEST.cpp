#include <iostream>
#include "lib/ScienceFictionLibrary.h"
#include "lib/Film.h" // Ensure the header defining Film is included
#include "lib/Serie.h" // Ensure the header defining Serie is included
#include "lib/VideoGame.h" // Ensure the header defining VideoGame is included
#include "lib/Book.h" // Ensure the header defining Book is included
#include "lib/Content.h" // Ensure the header defining Content is included
#include "lib/Comic.h" // Ensure the header defining Comic is included

int main(){
ScienceFiction_Library& library=ScienceFiction_Library::getInstance();
    ScienceFiction_Library& shownLibrary=ScienceFiction_Library::getShown();
    Film* film1=new Film();
    library.addContent(film1);
    film1->setImage("Image1");
    film1->setTitle("Film1");
    film1->setDescription("Description1");
    film1->setDirector("Director1");
    film1->setPhotoDirector("PhotoDirector1");
    film1->setProducer("Producer1");
    film1->setPlatforms("Platform1");
    film1->setDuration(120);
    film1->setStarred(true);
    film1->setWatched(false);
    film1->setYear(2023);
    film1->addSubgenre(1<<0);

    VideoGame* videgame1=new VideoGame();
    library.addContent(videgame1);
    videgame1->setImage("Image1");
    videgame1->setTitle("Film1");
    videgame1->setDescription("Description1");
    videgame1->setGameEngine("Director1");
    videgame1->setProducer("Producer1");
    videgame1->setPlatforms("Platform1");
    videgame1->setExpectedHours(120);
    videgame1->setStarred(true);
    videgame1->setWatched(false);
    videgame1->setYear(2023);
    videgame1->addSubgenre(2<<0);


    Serie* serie1=new Serie();
    library.addContent(serie1);
    serie1->setImage("Image1");
    serie1->setTitle("Film1");
    serie1->setDescription("Description1");
    serie1->setSeasons(5);
    serie1->setEpisodes(10);
    serie1->setCreator("PhotoDirector1");
    serie1->setProducer("Producer1");
    serie1->setPlatforms("Platform1");
    serie1->setDuration(120);
    serie1->setStarred(true);
    serie1->setWatched(false);
    serie1->setYear(2023);
    serie1->addSubgenre(4<<0);

    

    Book* book1=new Book();
    library.addContent(book1);
    book1->setImage("Image1");
    book1->setTitle("Film1");
    book1->setDescription("Description1");
    book1->setVolume(5);
    book1->setPages(10);
    book1->setAuthor("PhotoDirector1");
    book1->setMainCharacter("Producer1");
    book1->setPublisher("Platform1");
    book1->setStarred(true);
    book1->setWatched(false);
    book1->setYear(2023);
    book1->addSubgenre(4<<0);

    Comic* comic1=new Comic();
    library.addContent(comic1);
    comic1->setImage("Image1");
    comic1->setTitle("Film1");
    comic1->setDescription("Description1");
    comic1->setVolume(5);
    comic1->setPages(10);
    comic1->setAuthor("PhotoDirector1");
    comic1->setMainCharacter("Producer1");
    comic1->setPublisher("Platform1");
    comic1->setStarred(true);
    comic1->setWatched(false);
    comic1->setYear(2023);
    comic1->addSubgenre(4<<0); 
    comic1->setIllustrator("Illustrator1");
    comic1->setSerie("Series1");

    library.addContent(new Book("Book2", Subgenre::DRAMA, "Description2", false, true, 2022, "Image2", "Author2", "Publisher", 90, 1, "MainCharacter", 0));

    comic1->setInspiration(7);

    std::cout << "All content in the library:" << std::endl;
    library.testPrint(&library);

    std::cout << "\nFiltered content by title 'Film1':" << std::endl;
    library.filterContent("Film1");

    std::cout << "\nFiltered content by year 2022:" << std::endl;
    library.filterContent(2022);

    std::cout << "\nFiltered content by genre Action:" << std::endl;
    library.filterContent(Subgenre::ACTION);

    std::cout << "\nWatched content:" << std::endl;
    library.watchedOrNot(true);

    std::cout << "\nStarred content:" << std::endl;
    library.starredOrNot(true);

    return 0;


}
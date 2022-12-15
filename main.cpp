#include<iostream>
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "filesystem"
#include "vector"
#include "chrono"
#include "fstream"
#include "list"
#include "map"
#include <csignal>
std::string FetchFile(std::string FileName){
    std::string newFileName = "src/"+FileName;
    std::fstream FILE(newFileName,std::ios::in);
    std::string Content;
    if (FILE.is_open()){
        std::getline(FILE,Content);
    }
    FILE.close();
    return Content;
}
void PrintMessage(std::string TEXT){
    auto Element = ftxui::text(TEXT) | ftxui::bold | ftxui::underlined |ftxui::color(ftxui::Color::Black);
    auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(),ftxui::Dimension::Fit(Element));
    Render(screen, Element);
    screen.Print();
}
class Cache{
    struct CacheItems{
        std::string Key;
        std::string Value;
        CacheItems(std::string Key,std::string Value){
            this->Value=std::move(Value);
            this->Key=std::move(Key);
        }
    };
    int Capacity;
    std::list<CacheItems *> CacheList;
    std::map<std::string,CacheItems *> HASHMAP;
public:
    Cache(int Capacity){
        this->Capacity = Capacity;
    }
    void get(std::string Key){
        system("cls");
        if (HASHMAP.count(Key)){
            auto timeStart = std::chrono::steady_clock::now();
            auto LocalNode = HASHMAP[Key];
            for (auto i = CacheList.cbegin(); i != CacheList.cbegin();i++ ) {
                if (LocalNode==*i){
                    auto temp = CacheList.front();
                    CacheList.insert(i,temp);
                    CacheList.insert(CacheList.cbegin(),LocalNode);
                }
            }
            auto timeEnd = std::chrono::steady_clock::now();
            std::cout<<"Serving From ";
            PrintMessage("Cache");
            std::cout<<"\nThe Content of File "<<Key<<" is"<<"\nTime Taken "<<std::chrono::duration_cast<std::chrono::nanoseconds>(timeEnd-timeStart).count()<<"ms"<<std::endl <<"-----------------------------------"<<std::endl<<LocalNode->Value<<std::endl;
        }else{
            auto timeStart = std::chrono::steady_clock::now();
            auto TempNode = new CacheItems(Key, FetchFile(Key));
            if(CacheList.size()<Capacity){
                HASHMAP.emplace(Key, TempNode);
                CacheList.push_front(TempNode);
            }else{
                auto backElement = CacheList.back();
                HASHMAP.erase(backElement->Key);
                CacheList.pop_back();
                HASHMAP.emplace(Key, TempNode);
                CacheList.push_front(TempNode);
            }
            auto timeEnd = std::chrono::steady_clock::now();
            std::cout<<"Serving From ";
            PrintMessage("Main Source");
            std::cout<<"\nThe Content of File "<<Key<<" is"<<"\nSubsequent Search will be Faster \nTime Taken "<<std::chrono::duration_cast<std::chrono::nanoseconds>(timeEnd-timeStart).count()<<"ms"<<std::endl <<"-----------------------------------"<<std::endl<< TempNode->Value<<std::endl;
        }
    }
};
void GetFolderContent(std::vector<std::string> *fileItems){
std::filesystem::path folder(std::filesystem::current_path()/"src");
if (std::filesystem::is_directory(folder)){
    for (auto i : std::filesystem::directory_iterator(folder)) {
    std::filesystem::path item(i);
        std::string path_string{item.filename().u8string()};
    fileItems->push_back(path_string);
    }
    std::cout<<"File Indexing Completed";
}else{
std::filesystem::create_directories(std::filesystem::current_path()/"src");
std::cout<<"File Created"<<std::endl;
std::cout<<"Place Your File Inside Src Directory for caching";
}
}
 std::string RenderMenu(){
     std::vector<std::string> FileEntries ;
     GetFolderContent(&FileEntries);
  auto screen = ftxui::ScreenInteractive::TerminalOutput();
     int selected = 0;
     ftxui::MenuOption option;
     option.on_enter = screen.ExitLoopClosure();
     auto menu = Menu(&FileEntries, &selected, &option);
   screen.Loop(menu);
   return FileEntries.at(selected);
 }
void signal_callback_handler(int signum) {
    exit(signum);
}
int main(){
    signal(SIGINT, signal_callback_handler);
    Cache C1(2);
    int flag = 1;
    while(1){
        system("cls");
        std::string FileSelected = RenderMenu();
        C1.get(FileSelected);
        std::cin.get();
    }
}
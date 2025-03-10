//ladder_main.cpp
#include "ladder.h"

int main()
{
    //verify_word_ladder();

    string start{};
    string target{};
    cout<<"Enter start word: ";
    cin>>start;
    cout<<"Enter target word: ";
    cin>>target;
    if(start==target)
        error(start, target," is the same word as ");
    else
    {
        set<string> words;
        load_words(words,"src/words.txt");
        if(!words.contains(target))
            error(target,""," is not found in the English dictionary");
        else
            print_word_ladder(generate_word_ladder(start,target,words));
    }
    
}
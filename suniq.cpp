#include <map>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <list>
#include <iterator>
#include <unistd.h>
#include <stdio.h>

int main( int argc, char * argv [] ){
    std::string line;
    std::map<std::string, int> line_map;
    int i(2);
    std::list <std::string> args;
    // read in arguments
    for ( ; i < argc+1; ++i) {
        args.push_back( std::string(argv[i-1] ));
    }
    // check if -r supplied
    bool reverse = args.end () != find(args.begin(), args.end(), "-r");
    std::list<std::istream *> streams;
    // check if we're dealing with data being piped in or as file arguments
    if (isatty(fileno(stdin))){
        std::list<std::string>::iterator argiter = args.begin();
        while ( argiter != args.end() ){
            std::ifstream * fp = new std::ifstream(((*(argiter)).c_str()));
            if (fp->good())
                streams.push_back( fp );
            ++argiter;
        }
    }
    else
        streams.push_back( &std::cin );
    std::list<std::istream *>::iterator streamiter = streams.begin();
    // read in all lines
    while ( streamiter != streams.end()) { 
        while ( getline(**(streamiter), line) ){
            auto iterp = line_map.insert( { line , 1 } );
            if ( !iterp.second ){
                ++iterp.first->second;
            }
        }
        // don't free up cin
        if ( **streamiter  != std::cin  && ((std::ifstream *)(*streamiter))->is_open()){
            ((std::ifstream *)(*streamiter))->close();
            delete *streamiter;
        }
        ++streamiter;
    }
    // flip the map so we can print by occurence
    std::multimap<int , std::string> flipped;
    for (const auto &p : line_map ){
        flipped.insert({p.second, p.first});
    }
    std::multimap<int, std::string>::iterator iter = reverse ? flipped.end() : flipped.begin() ;
    if ( reverse )
        iter--;

    while ( iter != (reverse ? flipped.begin() : flipped.end()) ){
        std::cout << "\t" << iter->first << "\t" << iter->second <<  std::endl;
        reverse  ? --iter : ++iter;
    }
    if ( reverse ){
        std::cout << "\t" << iter->first << "\t" << iter->second <<  std::endl;
    }
}

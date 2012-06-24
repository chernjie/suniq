#include <map>
#include <iostream>
#include <fstream>
#include <set>
#include <list>
#include <stdio.h>

template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
    return std::pair<B,A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B,A> flip_map(const std::map<A,B> &src)
{
    std::multimap<B,A> dst;
    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), 
                   flip_pair<A,B>);
    return dst;
}


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
        while ( !(**streamiter).eof() ){
            line_map[line] = line_map[line]+1;
            getline(**(streamiter), line);
        }
        // don't free up cin
        if ( **streamiter  != std::cin  && ((std::ifstream *)(*streamiter))->is_open()){
            ((std::ifstream *)(*streamiter))->close();
            delete *streamiter;
        }
        ++streamiter;
    }
    // flip the map so we can print by occurence
    std::multimap<int , std::string> flipped = flip_map ( line_map );
    std::multimap<int, std::string>::iterator iter = reverse ? flipped.end() : flipped.begin() ;
    if ( reverse )
        iter--;
    while ( iter != (reverse ? flipped.begin() : flipped.end()) ){
        std::cout << iter->first << " " << iter->second <<  std::endl;
        reverse  ? --iter : ++iter;
    }
    if ( reverse )
        std::cout << iter->first << " " << iter->second <<  std::endl;
}

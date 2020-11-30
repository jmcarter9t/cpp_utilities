#include "utilities.hpp"
#include <iostream>
#include <cmath>

const std::string utilities::DELIMITERS = " \f\n\r\t\v";
const std::string utilities::QUOTES = "\"\'";

std::size_t UInt64PairHash::operator()( const UInt64Pair& p ) const 
{
    return p.first * 31 + p.second;
}

StrVector utilities::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}
    
std::string utilities::string_replace(const std::string& str, const std::string& match, const std::string& replacement, unsigned int max_replacements )
{
    size_t pos = 0;
    std::string newstr = str;
    unsigned int replacements = 0;
    while ((pos = newstr.find(match, pos)) != std::string::npos
            && replacements < max_replacements)
    {
         newstr.replace(pos, match.length(), replacement);
         pos += replacement.length();
         replacements++;
    }
    return newstr;
}

std::string& utilities::dequote( std::string& s )
{
  s.erase( s.find_last_not_of( utilities::QUOTES ) + 1 );
  return s.erase( 0, s.find_first_not_of( utilities::QUOTES ) );
}

std::string& utilities::rstrip( std::string& s )
{
  return s.erase( s.find_last_not_of( utilities::DELIMITERS ) + 1 );
}

std::string& utilities::lstrip( std::string& s )
{
  return s.erase( 0, s.find_first_not_of( utilities::DELIMITERS ) );
}

std::string& utilities::strip( std::string& s )
{
  return utilities::lstrip( rstrip ( s ));
}

StrPair utilities::split_attribute( const std::string& s, char delim) {
    StrPair r;
    size_t pos = s.find(delim);
    if (pos < std::string::npos) {
        r.first = s.substr(0,pos);
        pos += 1;
        if (pos < std::string::npos) {
            r.second = s.substr(pos,s.size());
        }
    } 
    return r;
}

bool utilities::are_equal(double a, double b, double epsilon) {
    return std::fabs(a - b) < epsilon;
}

bool utilities::directory_exists( const std::string& path )
{
    struct stat info;

    if ( stat( path.c_str(), &info ) != 0 ) {
        return false;
    } 
    
    return ( info.st_mode & S_IFDIR );
}

bool utilities::make_directory( const std::string& path, mode_t mode )
{
    struct stat info;
    int status = 0;         // success.

    if ( stat( path.c_str(), &info ) != 0 ) {
        // file doesn't exist
        if ( mkdir( path.c_str(), mode ) != 0 && errno != EEXIST ) {
            // error returned that was NOT file already exists
            status = -1;
        }
    }  else if ( !S_ISDIR( info.st_mode ) ) {
        // exists and is a directory.
        errno = ENOTDIR;
        status = -1;
    }
    
    return ( status );
}

Timer::Timer()
    : beg_(clock_::now())
{}

void Timer::reset() 
{ 
    beg_ = clock_::now(); 
}

double Timer::elapsed() const
{ 
    return std::chrono::duration_cast<second_> (clock_::now() - beg_).count();
}

int BinarySearch::find( std::pair<int,int> interval, const std::vector<int>& v )
{
    int left = 0;
    int right = v.size();

    if ( interval.first < interval.second )
    {
        // the [x,y) interval is defined properly -- not empty.
        while (left <= right)
        {
            size_t mid = left + (right-left)/2;

            if ( interval.first <= v[mid] && v[mid] < interval.second )
            {
                // value in the interval: [first, second)
                return v[mid];
            }

            if (v[mid] < interval.first)
            {
                // value is less than the left closed interval bounds; move left search point.
                left = mid + 1;
            }
            else // v[mid] not within interval and v[mid] >= interval.first
            {
                right = mid - 1;
            }
        }
    }

    // if we reach here, then element was not present
    return -1;
}

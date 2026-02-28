#include <string>
#include "movies.h"

#define UTILITIES_H

class utilities{
    public:
        
        struct alphabetical{
            bool operator()(const movies& m1, const movies& m2) const{
                return m1.getTitle() < m2.getTitle();
            };
        };

        struct numericalDecreasing{
            bool operator()(const movies& m1, const movies& m2) const{
                return m1.getRating() < m2.getRating();
            };
        };
};

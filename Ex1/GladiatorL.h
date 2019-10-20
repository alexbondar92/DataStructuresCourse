//
//  GladiatorL.h
//  DataStructure-wet1
//
#ifndef GladiatorL_H_
#define GladiatorL_H_

#include <stdio.h>

namespace DS {
    class GladiatorL{
        int Id;
        int level;
        
    public:
        GladiatorL();
        GladiatorL(int ID, int level);
        GladiatorL(const GladiatorL& gladiator);
        GladiatorL& operator=(const GladiatorL& gladiator);
        bool operator<(const GladiatorL& gladi);
        bool operator==(const GladiatorL& gladi) const;
        bool operator>(const GladiatorL& gladi);
        bool operator!=(const GladiatorL& gladi) const;
        
        int getId() const;
        
        int getLevel() const;
        
        void setId(int new_id);
        
        void setLevel(int new_level);
        
        
    };
}
#endif /* GladiatorL_H_ */

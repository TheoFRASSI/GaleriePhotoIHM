#ifndef SMARTDELETE_H
#define SMARTDELETE_H

template <typename T>
void smartDeleteMrNovelli(T* p){
    if(p != nullptr){
        delete p;
        p = nullptr;
    }
}

#endif // SMARTDELETE_H

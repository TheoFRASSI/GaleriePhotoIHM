#ifndef SMARTDELETE_H
#define SMARTDELETE_H

// destructeur intelligent de pointeurs

template <typename T>
void smartDeleteMrNovelli(T* p){
    if(p != nullptr){
        delete p;
        p = nullptr;
    }
}

#endif // SMARTDELETE_H

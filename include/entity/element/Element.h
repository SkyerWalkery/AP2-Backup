#ifndef AP_PROJ_ELEMENT_H
#define AP_PROJ_ELEMENT_H


enum class Element{
    // Basic elements
    PYRO = 1,
    HYDRO,
    CYRO,
    ANEMO,

    // elements that are mainly from reactions
    FROZEN, // Hydro and Cyro, which will stop an entity from moving for a while
};

#endif //AP_PROJ_ELEMENT_H

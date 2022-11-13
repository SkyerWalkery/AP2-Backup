#ifndef AP_PROJ_ACTION_H
#define AP_PROJ_ACTION_H

// #include "Entity.h"
class Entity;

/**
 * Base class of all action
 * An Action is between two Entities (initiator and acceptor).
 * May be attack, of other effect.
 */

class Action{

    Entity* initiator_;
    Entity* acceptor_;

public:

    explicit Action(Entity* initiator = nullptr, Entity* acceptor = nullptr);

    // Getters and setters
    Entity* getInitiator() const;

    void setInitiator(Entity* initiator);

    Entity* getAcceptor() const;

    void setAcceptor(Entity* acceptor);

};

#endif //AP_PROJ_ACTION_H

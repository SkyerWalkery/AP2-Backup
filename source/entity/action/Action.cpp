#include "Action.h"

Action::Action(Entity *initiator, Entity *acceptor): initiator_(initiator), acceptor_(acceptor) {

}

Entity *Action::getInitiator() const {
    return initiator_;
}

void Action::setInitiator(Entity *initiator) {
    initiator_ = initiator;
}

Entity *Action::getAcceptor() const {
    return acceptor_;
}

void Action::setAcceptor(Entity *acceptor) {
    acceptor_ = acceptor;
}

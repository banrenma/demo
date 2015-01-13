#ifndef  __STATE_MACHINE__
#define __STATE_MACHINE__

#include "Util.h"
class Util;

class State
{
public:
	virtual ~State(){};
	virtual void EnterState(Util * o) = 0;
	virtual void ExecuteState(Util *o) = 0;
	virtual void ExitState(Util *o) = 0;
	virtual void OnMessage(Util *o) = 0;

};



class StateMachine
{
	CC_SYNTHESIZE(State *,m_poCurState,CurState)
	CC_SYNTHESIZE(State *,m_poPreState,PreState)
	CC_SYNTHESIZE(State *,m_poGlobleState,GlobleState)


	//void update();







};


#endif
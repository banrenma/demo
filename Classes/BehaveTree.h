#ifndef __BEHAVETREE__
#define __BEHAVETREE__

#include "cocos2d.h"
class Behavior
{
public:
	static int s_BehaviorID;
public:
	Behavior(){
		m_iID = s_BehaviorID;
		s_BehaviorID++;
	}
	virtual void destory(){};
	virtual bool visit(){return true;};
	~Behavior(){destory();}
	CC_SYNTHESIZE(int,m_iID,ID)
};
int Behavior::s_BehaviorID = 0;

// 组合 节点
class  CompositeNode:public Behavior
{
public:
	CompositeNode(){m_vecChild.empty();}
	~ CompositeNode(){
		destory();
	}

	virtual void destory(){
		std::vector<Behavior *>::iterator it;
		for(it = m_vecChild.begin(); it != m_vecChild.end(); it++)
		{
			if((*it) != NULL)
			{
				(*it)->destory();
			}
			delete (*it);
		}
	};

	virtual bool visit(){return true;}
	virtual void addChild(Behavior * child){ m_vecChild.push_back(child);};
	virtual void removeChild(int  id)
	{
		std::vector<Behavior *>::iterator it;
		for(it = m_vecChild.begin(); it != m_vecChild.end(); it++)
		{
			if((*it)->getID() == id)
			{
				(*it)->destory();
				delete (*it);
				m_vecChild.erase(it);
				return; 
			}
		}	
	};
	virtual void removeAllChild()
	{
		destory();
		m_vecChild.empty();
	}
protected:
	std::vector<Behavior *> m_vecChild;
};

class SelectorNode:public CompositeNode
{
public:
	SelectorNode(){}
	~SelectorNode(){}
	virtual bool visit()
	{
		std::vector<Behavior *>::iterator it;
		for(it = m_vecChild.begin(); it != m_vecChild.end(); it++)
		{
			if((*it)->visit())
			{
				return true;
			}
		}
		return false;
	};
};


class SequenceNode:public CompositeNode
{
public:
	SequenceNode(){}
	~SequenceNode(){}
	virtual bool visit()
	{
		std::vector<Behavior *>::iterator it;
		for(it = m_vecChild.begin(); it != m_vecChild.end(); it++)
		{
			if(!(*it)->visit())
			{
				return false;
			}
		}
		return true;
	};
};
//
class ParallelFallNode:public CompositeNode
{
public:
	ParallelFallNode(){}
	~ParallelFallNode(){}
	virtual bool visit()
	{
		bool ret = false;
		std::vector<Behavior *>::iterator it;
		for(it = m_vecChild.begin(); it != m_vecChild.end(); it++)
		{
			if((*it)->visit())
			{
				ret = true;
			}
		}
		return ret;
	};
};


class ParallelSucceedNode:public CompositeNode
{
public:
	ParallelSucceedNode(){}
	~ParallelSucceedNode(){}
	virtual bool visit()
	{
		bool ret = true;
		std::vector<Behavior *>::iterator it;
		for(it = m_vecChild.begin(); it != m_vecChild.end(); it++)
		{
			if(!(*it)->visit())
			{
				ret = false;
			}
		}
		return ret;
	};
};


class ParallelHybirdNode:public CompositeNode
{
public:
	ParallelHybirdNode():m_iJudgeCount(0){}
	ParallelHybirdNode(int JudgeCount):CompositeNode()
	{
		m_iJudgeCount = JudgeCount;
	}
	~ParallelHybirdNode(){}
	virtual bool visit()
	{
		int count = 0;
		std::vector<Behavior *>::iterator it;
		for(it = m_vecChild.begin(); it != m_vecChild.end(); it++)
		{
			if((*it)->visit())
			{
				count++;
			}
		}
		if(count >= m_iJudgeCount)
		{
			return true;
		}
		return false;
	};
	CC_SYNTHESIZE(int,m_iJudgeCount,JudgeCount)
};
//条件节点
typedef std::function<bool()>BehaviorCallback;

typedef std::function<bool()>BehaviorCallbackEvent;

class BehaviorLeafNode:public Behavior
{
public:
	BehaviorLeafNode(){}
	BehaviorLeafNode(const BehaviorCallback &callback)
	{
		this->m_pFunbehaviorCallback = callback;
	}
	virtual bool visit(){return m_pFunbehaviorCallback();}
	void setBehaviorCallback(const BehaviorCallback &callback)
	{
		this->m_pFunbehaviorCallback = callback;
	}
	~BehaviorLeafNode(){}
protected:
	BehaviorCallback m_pFunbehaviorCallback;
};


class ConditionNode:public BehaviorLeafNode
{
public:
	ConditionNode(){}
	ConditionNode(const BehaviorCallback &callback):BehaviorLeafNode(callback)
	{
		
	}
	~ConditionNode(){}
};
class ActionNode:public BehaviorLeafNode
{
public:
	ActionNode(){}
	ActionNode(const BehaviorCallback &callback):BehaviorLeafNode(callback)
	{
	}
	~ActionNode(){}
};

#endif
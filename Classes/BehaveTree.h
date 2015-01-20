#ifndef __BEHAVETREE__
#define __BEHAVETREE__

#include "cocos2d.h"
USING_NS_CC;
//�޸ķ���״̬��  �´� д��ʱ�� ��Ҫ���� true or false  ����һЩ״̬��



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


// ��� �ڵ�
class  CompositeNode:public Behavior
{
public:
	CompositeNode(){m_vecChild.clear();}
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
		m_vecChild.clear();
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
//�����ڵ�
typedef std::function<bool()>BehaviorLeafCallback;



class BehaviorLeafNode:public Behavior
{
public:
	BehaviorLeafNode(){}
	BehaviorLeafNode(const BehaviorLeafCallback &callback)
	{
		this->m_pFunbehaviorCallback = callback;
	}
	virtual bool visit(){return m_pFunbehaviorCallback();}
	void setBehaviorCallback(const BehaviorLeafCallback &callback)
	{
		this->m_pFunbehaviorCallback = callback;
	}
	~BehaviorLeafNode(){}
protected:
	BehaviorLeafCallback m_pFunbehaviorCallback;
	
};



class ConditionNode:public BehaviorLeafNode
{
public:
	ConditionNode(){}
	ConditionNode(const BehaviorLeafCallback &callback):BehaviorLeafNode(callback)
	{
		
	}
	~ConditionNode(){}
};
class ActionNode:public BehaviorLeafNode
{
public:
	ActionNode(){}
	ActionNode(const BehaviorLeafCallback &callback):BehaviorLeafNode(callback)
	{
	}
	~ActionNode(){}
};



typedef std::function<bool(Behavior *)>BehaviorNodeCallback;

class DecoratorBeforeAndEndNode:public Behavior
{

public:
	DecoratorBeforeAndEndNode():m_pChild(NULL){}
	DecoratorBeforeAndEndNode(Behavior *m_pChild,const BehaviorNodeCallback &beforecallback,const BehaviorNodeCallback &endcallback)
	{
		this->m_pChild = m_pChild;
		this->m_pBeforeFunbehaviorCallback = beforecallback;
		this->m_pEndFunbehaviorCallback = endcallback;
	}
	virtual bool visit(){
		bool ret = false;
		ret = m_pBeforeFunbehaviorCallback(this);
		if(ret)
		{
			return true;
		}
		if(m_pChild)
		{
			ret = m_pChild->visit();
		}
		ret = m_pEndFunbehaviorCallback(this);
		return ret;
	}
	void setBeforeBehaviorCallback(const BehaviorNodeCallback &callback)
	{
		this->m_pBeforeFunbehaviorCallback = callback;
	}
	void setEndBehaviorCallback(const BehaviorNodeCallback &callback)
	{
		this->m_pEndFunbehaviorCallback = callback;
	}
	~DecoratorBeforeAndEndNode(){}
protected:
	Behavior *m_pChild;
	BehaviorNodeCallback m_pBeforeFunbehaviorCallback;
	BehaviorNodeCallback m_pEndFunbehaviorCallback;
};

class DecoratorEndNode:public Behavior
{

public:
	DecoratorEndNode():m_pChild(NULL){}
	DecoratorEndNode(Behavior *m_pChild,const BehaviorNodeCallback &endcallback)
	{
		this->m_pChild = m_pChild;
		this->m_pEndFunbehaviorCallback = endcallback;
	}
	virtual bool visit(){
		bool ret = false;
		if(m_pChild)
		{
			ret = m_pChild->visit();
		}
		ret = m_pEndFunbehaviorCallback(this);
		return ret;
	}

	void setEndBehaviorCallback(const BehaviorNodeCallback &callback)
	{
		this->m_pEndFunbehaviorCallback = callback;
	}
	~DecoratorEndNode(){}
protected:
	Behavior *m_pChild;
	BehaviorNodeCallback m_pEndFunbehaviorCallback;
};


class DecoratorBeforeNode:public Behavior
{

public:
	DecoratorBeforeNode():m_pChild(NULL){}
	DecoratorBeforeNode(Behavior *m_pChild,const BehaviorNodeCallback &beforecallback)
	{
		this->m_pChild = m_pChild;
		this->m_pBeforeFunbehaviorCallback = beforecallback;
	}
	virtual bool visit(){
		bool ret = false;
		m_pBeforeFunbehaviorCallback(this);
		if(m_pChild)
		{
			ret = m_pChild->visit();
		}
		return ret;
	}
	void setBeforeBehaviorCallback(const BehaviorNodeCallback &callback)
	{
		this->m_pBeforeFunbehaviorCallback = callback;
	}
	~DecoratorBeforeNode(){}
protected:
	Behavior *m_pChild;
	BehaviorNodeCallback m_pBeforeFunbehaviorCallback;
};


#endif
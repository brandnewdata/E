// ���� ��ũ�� ����Ʈ ����
#pragma once

template <typename T>
class ListNode
{
	template <typename T>
	friend class DoubleLinkedList;

	template <typename T>
	friend class DoubleLinkedListIterator;

	template <typename T>
	friend class DoubleLinkedListReverse;

private:
	ListNode()
	{

	}

	~ListNode()
	{

	}

private:
	ListNode* m_pPrev = nullptr;
	ListNode* m_pNext = nullptr;

	T m_Data;
};

template <typename T>
class DoubleLinkedListIterator
{

	template <typename T>
	friend class DoubleLinkedList;

public:
	DoubleLinkedListIterator()
	{

	}

	~DoubleLinkedListIterator()
	{

	}

private:
	typedef ListNode<T>*	PNODE;

private:
	PNODE m_pNode;

public:
	bool operator == (const DoubleLinkedListIterator<T>& iter)
	{
		return m_pNode == iter.m_pNode;
	}

	bool operator != (const DoubleLinkedListIterator<T>& iter)
	{
		return m_pNode != iter.m_pNode;
	}

	// �ε����� �����ø� ���� ���� �ε����� �̵��Ѵ�.
	void operator ++ ()
	{
		m_pNode = m_pNode->m_pNext;
	}

	void operator -- ()
	{
		m_pNode = m_pNode->m_pPrev;
	}

	T& operator * ()
	{
		return m_pNode->m_Data;
	}
};

template <typename T>
class DoubleLinkedListReverseIterator
{

	template <typename T>
	friend class DoubleLinkedList;

public:
	DoubleLinkedListReverseIterator()
	{

	}

	~DoubleLinkedListReverseIterator()
	{

	}

private:
	typedef ListNode<T>* PNODE;

private:
	PNODE m_pNode;

public:
	bool operator == (const DoubleLinkedListReverseIterator<T>& iter)
	{
		return m_pNode == iter.m_pNode;
	}

	bool operator != (const DoubleLinkedListReverseIterator<T>& iter)
	{
		return m_pNode != iter.m_pNode;
	}

	// �����ڰ� �ݴ�� �۵��Ѵ�.
	void operator -- ()
	{
		m_pNode = m_pNode->m_pNext;
	}

	void operator ++ ()
	{
		m_pNode = m_pNode->m_pPrev;
	}

	T& operator * ()
	{
		return m_pNode->m_Data;
	}
};

template <typename T>
class DoubleLinkedList
{
public:
	DoubleLinkedList()
	{
		m_Begin = new NODE;
		m_End = new NODE;
	}

	~DoubleLinkedList()
	{
		Clear();
		delete m_Begin;
		delete m_End;
	}

private:
	typedef ListNode<T>* PNODE;
	typedef ListNode<T>		NODE;
	int m_nSize = 0;

private:
	PNODE	m_Begin;
	PNODE	m_End;

public:
	typedef DoubleLinkedListIterator<T> iterator;
	typedef DoubleLinkedListReverseIterator<T> reverse_iterator;

public:

	int GetSize()
	{
		return m_nSize;
	}

	void Push_Back(const T& Data)
	{
		PNODE pNode = new NODE;

		if (m_End->m_pPrev == nullptr)
		{
			// ���Ե� ���� m_BeginNode ����
			m_Begin->m_pNext = pNode;
			pNode->m_pPrev = m_Begin;
		}
		else
		{
			// ���Ե� ���� ���� ������ ��� ����
			m_End->m_pPrev->m_pNext = pNode;
			pNode->m_pPrev = m_End->m_pPrev;
		}


		// m_End ���� ���Ե� ��带 ����
		m_End->m_pPrev = pNode;
		pNode->m_pNext = m_End;

		// ��忡 �����͸� ����
		pNode->m_Data = Data;

		m_nSize++;

	}

	void Push_Front(const T& Data)
	{
		PNODE pNode = new NODE;

		if (m_Begin->m_pNext == nullptr)
		{
			// m_End Node�� ���Ե� ��忬��
			pNode->m_pNext = m_End;
			m_End->m_pPrev = pNode;
		}
		else
		{
			// ���Ե� ���� ���� ù��° ����� ����
			m_Begin->m_pNext->m_pPrev = pNode;
			pNode->m_pNext = m_Begin->m_pPrev;
		}

		// m_Begin ���� ���Ե� ��� ����
		m_Begin->m_pNext = pNode;
		pNode->m_pPrev = m_Begin;

		// ��忡 �����͸� ����
		pNode->m_Data = Data;

		m_nSize++;
	}

	T Pop_Front()
	{
		// ù��° ����� Data�� ����
		T Data = m_Begin->m_pNext->m_Data;

		// m_Begin�� ���� ���� �ι�° ��带 ����
		m_Begin->m_pNext = m_Begin->m_pNext->m_pNext;

		//����带 ����
		delete m_Begin->m_pNext->m_pPrev;

		// ù��°�� �� �ι�° ����� �� ��带 m_Begin���� ����
		m_Begin->m_pNext->m_pPrev = m_Begin;

		m_nSize--;

		return Data;
	}

	T Pop_Back()
	{
		// ������ ����� Data�� ����
		T Data = m_End->m_pPrev->m_Data;

		// n��尡 ������ ����϶�
		// n-1��带 m_End�� �� ���� ����.
		m_End->m_pPrev = m_End->m_pPrev->m_pPrev;

		//����带 ����
		delete m_End->m_pPrev->m_pNext;

		// n-1����� �� ���� m_End ��带 ����
		m_End->m_pPrev->m_pNext = m_End;

		m_nSize--;

		return Data;
	}

	void Clear()
	{
		for (m_nSize; m_nSize > 0; --m_nSize)
		{
			// n��尡 ������ ����϶�
				// n-1��带 m_End�� �� ���� ����.
			m_End->m_pPrev = m_End->m_pPrev->m_pPrev;

			//����带 ����
			delete m_End->m_pPrev->m_pNext;

			// n-1����� �� ���� m_End ��带 ����
			m_End->m_pPrev->m_pNext = m_End;

		}
	}

	bool Empty()
	{
		if (m_nSize > 0)
			return false;
		else
			return true;
	}

public:
	// ���� ù��° ��Ұ� ����ִ� ��Ҹ� �������ϴ� �ݺ��ڸ� ��ȯ�Ѵ�.
	iterator Begin() const
	{
		iterator iter;
		iter.m_pNode = m_Begin->m_pNext;

		return iter;
	}

	iterator End() const
	{
		// (] ���� �󱸰��ΰ� �ݺ��� ���� =���� <> �ϱ� ���ؼ� �װ� ���� ����.
		iterator iter;
		iter.m_pNode = m_End;

		return iter;
	}

};
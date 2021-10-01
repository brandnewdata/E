// 더블 링크드 리스트 구현
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

	// 인덱스를 증가시면 다음 노드로 인덱스가 이동한다.
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

	// 연산자가 반대로 작동한다.
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
			// 삽입된 노드와 m_BeginNode 연결
			m_Begin->m_pNext = pNode;
			pNode->m_pPrev = m_Begin;
		}
		else
		{
			// 삽입된 노드와 이전 마지막 노드 연결
			m_End->m_pPrev->m_pNext = pNode;
			pNode->m_pPrev = m_End->m_pPrev;
		}


		// m_End 노드와 삽입되 노드를 연결
		m_End->m_pPrev = pNode;
		pNode->m_pNext = m_End;

		// 노드에 데이터를 저장
		pNode->m_Data = Data;

		m_nSize++;

	}

	void Push_Front(const T& Data)
	{
		PNODE pNode = new NODE;

		if (m_Begin->m_pNext == nullptr)
		{
			// m_End Node와 삽입된 노드연결
			pNode->m_pNext = m_End;
			m_End->m_pPrev = pNode;
		}
		else
		{
			// 삽입된 노드와 이전 첫번째 노드의 연결
			m_Begin->m_pNext->m_pPrev = pNode;
			pNode->m_pNext = m_Begin->m_pPrev;
		}

		// m_Begin 노드와 삽입된 노드 연결
		m_Begin->m_pNext = pNode;
		pNode->m_pPrev = m_Begin;

		// 노드에 데이터를 저장
		pNode->m_Data = Data;

		m_nSize++;
	}

	T Pop_Front()
	{
		// 첫번째 노드의 Data를 복사
		T Data = m_Begin->m_pNext->m_Data;

		// m_Begin의 다음 노드로 두번째 노드를 지정
		m_Begin->m_pNext = m_Begin->m_pNext->m_pNext;

		//현노드를 삭제
		delete m_Begin->m_pNext->m_pPrev;

		// 첫번째가 된 두번째 노드의 앞 노드를 m_Begin으로 설정
		m_Begin->m_pNext->m_pPrev = m_Begin;

		m_nSize--;

		return Data;
	}

	T Pop_Back()
	{
		// 마지막 노드의 Data를 복사
		T Data = m_End->m_pPrev->m_Data;

		// n노드가 마지막 노드일때
		// n-1노드를 m_End의 앞 노드로 지정.
		m_End->m_pPrev = m_End->m_pPrev->m_pPrev;

		//현노드를 삭제
		delete m_End->m_pPrev->m_pNext;

		// n-1노드의 뒤 노드로 m_End 노드를 지정
		m_End->m_pPrev->m_pNext = m_End;

		m_nSize--;

		return Data;
	}

	void Clear()
	{
		for (m_nSize; m_nSize > 0; --m_nSize)
		{
			// n노드가 마지막 노드일때
				// n-1노드를 m_End의 앞 노드로 지정.
			m_End->m_pPrev = m_End->m_pPrev->m_pPrev;

			//현노드를 삭제
			delete m_End->m_pPrev->m_pNext;

			// n-1노드의 뒤 노드로 m_End 노드를 지정
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
	// 실제 첫번째 요소가 들어있는 요소를 포인팅하는 반복자를 반환한다.
	iterator Begin() const
	{
		iterator iter;
		iter.m_pNode = m_Begin->m_pNext;

		return iter;
	}

	iterator End() const
	{
		// (] 끝은 폐구간인게 반복문 에서 =없이 <> 하기 편해서 그게 보기 편함.
		iterator iter;
		iter.m_pNode = m_End;

		return iter;
	}

};
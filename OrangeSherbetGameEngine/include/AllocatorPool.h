//#pragma once
//
//#ifndef ALLOCATOR_POOL_H
//
//template <typename T, size_t BlockSize = 4096>
//class AllocatorPool
//{
//public:
//	AllocatorPool(T type, int size);
//	~AllocatorPool();
//
//	T* AllocateChunk();
//	void RemoveChunk(T*);
//
//private:
//	union Slot_ {
//		T element;
//		Slot_* next;
//	};
//
//	T* empty;
//	T* full;
//
//
//	int size;
//	
//};
//
//
//#endif // !ALLOCATOR_POOL_H

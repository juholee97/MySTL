#pragma once
#include <algorithm>
#include <memory>
#include <new>

/// <summary>
/// My Vector를 구현하기 위한 template
/// </summary>
/// <typeparam name="_Ty">
/// 해당 타입은 MyVector에 저장할 데이터의 타입을 의미함.
/// </typeparam>
/// <typeparam name="Allocator">
/// 해당 타입은 vector memory의 할당을 관리
/// </typeparam>

template < typename _Ty, typename Allocator = std::allocator< _Ty > >
class MyVector
{
private :
	static constexpr size_t DEFAULT_CAPACITY_SIZE = 10;
public :
	using value_type = _Ty;
	using iterator = value_type*;

	explicit MyVector( const size_t count,
					   const value_type value,
					   const Allocator& alloc = Allocator() )
		: m_Allocator( alloc )
	{
		AllocCapacity( count );
		m_Size = count;
		std::uninitialized_fill( begin(), end(), value );
	}

	explicit MyVector( const size_t count = DEFAULT_CAPACITY_SIZE,
					   const Allocator& alloc = Allocator() )
		: m_Allocator( alloc )
	{
		AllocCapacity( count );
	}

	MyVector( const MyVector& _Other,
			  const Allocator& alloc = Allocator() )
		: m_Allocator( alloc )
	{
		AllocCapacity( _Other.m_CapacitySize );
		std::uninitialized_copy( _Other.begin(), _Other.end(), m_pData );
		m_Size = _Other.size();
	}

	MyVector( MyVector&& _Other ) noexcept
	{
		std::swap( m_CapacitySize, _Other.m_CapacitySize );
		std::swap( m_Size, _Other.m_Size );
		std::swap( m_pData, _Other.m_pData );
		std::swap( m_Allocator, _Other.m_Allocator );
	}

	~MyVector()
	{
		DeAllocateCapacity();
	}
};
        #include <cmath>
	#include <iostream>

        template <class Comparable>
        BinaryHeap<Comparable>::BinaryHeap( int capacity )
          : array( capacity + 1 ), currentSize( 0 )
        {
        }

        template <class Comparable>
        void BinaryHeap<Comparable>::insert( const Comparable & x )
        {
            if( isFull( ) )
                throw Overflow( );

                // Percolate up
            int hole = ++currentSize;
            for( ; hole > 1 && x < array[ hole / 2 ]; hole /= 2 )
                array[ hole ] = array[ hole / 2 ];
            array[ hole ] = x;
        }

        template <class Comparable>
        const Comparable & BinaryHeap<Comparable>::findMin( ) 
        {
            if( isEmpty( ) )
                throw Underflow( );
            return array[ 1 ];
        }


	template <class Comparable>
	const Comparable & BinaryHeap<Comparable>::findMax( ) 
	{

		// INSERT CODE FOR findMax HERE
		if (isEmpty())	
		{
     		   throw Underflow();
    		}		
    		int loc = int (pow(2.0,Height()));
    		int maxLoc = loc; 
   		 loc++;
   		 while (loc <= currentSize)
	         {
        		if(array[loc] > array[maxLoc])
			{
        		    maxLoc = loc;
        		    loc++;
        		}
        	else 
            		loc++;
    		}	
    		return array[maxLoc];

	} 


	
	template <class Comparable>
	void BinaryHeap<Comparable> :: printLtSubtree()
	{
		if(isEmpty())
		{
			throw Underflow();
		}
		else
		{
			printLtSubtree(2);
		}
	}

	template <class Comparable>
        void BinaryHeap<Comparable> :: printLtSubtree(int i) 
	{

		// INSERT CODE for printLtSubtree HERE
		if (i <= currentSize)
		{
        		cout << array[i] << " ";
        		printLtSubtree(i*2);
        		printLtSubtree(2*i+1);
    		}	

	}




        template <class Comparable>
       	int BinaryHeap<Comparable> :: Height() const
	{

		// INSERT CODE for Height HERE
		int h = -1;
    		while (((pow(2,(h+1)))-1) < currentSize)		
		{
     			h++;
    		}
  	 	 return h;	
		

        }

		
        template <class Comparable>
        void BinaryHeap<Comparable>::deleteMin( )
        {
            if( isEmpty( ) )
                throw Underflow( );

            array[ 1 ] = array[ currentSize-- ];
            percolateDown( 1 );
        }

        template <class Comparable>
        void BinaryHeap<Comparable>::deleteMin( Comparable & minItem )
        {
            if( isEmpty( ) )
                throw Underflow( );

            minItem = array[ 1 ];
            array[ 1 ] = array[ currentSize-- ];
            percolateDown( 1 );
        }

        template <class Comparable>
        void BinaryHeap<Comparable>::buildHeap( )
        {
            for( int i = currentSize / 2; i > 0; i-- )
                percolateDown( i );
        }

        template <class Comparable>
        bool BinaryHeap<Comparable>::isEmpty( ) const
        {
            return currentSize == 0;
        }

        template <class Comparable>
        bool BinaryHeap<Comparable>::isFull( ) const
        {
            return currentSize == array.size( ) - 1;
        }

        template <class Comparable>
        void BinaryHeap<Comparable>::makeEmpty( )
        {
            currentSize = 0;
        }

        template <class Comparable>
        void BinaryHeap<Comparable>::percolateDown( int hole )
        {
/* 1*/      int child;
/* 2*/      Comparable tmp = array[ hole ];

/* 3*/      for( ; hole * 2 <= currentSize; hole = child )
            {
/* 4*/          child = hole * 2;
/* 5*/          if( child != currentSize && array[ child + 1 ] < array[ child ] )
/* 6*/              child++;
/* 7*/          if( array[ child ] < tmp )
/* 8*/              array[ hole ] = array[ child ];
                else
/* 9*/              break;
            }
/*10*/      array[ hole ] = tmp;
        }

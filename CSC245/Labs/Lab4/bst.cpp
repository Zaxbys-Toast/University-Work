        #include <iostream>
        #include <cstdlib>
        using namespace std;

        template <class Comparable>
        BinarySearchTree<Comparable>::BinarySearchTree( const Comparable & notFound ) :
          ITEM_NOT_FOUND( notFound ), root( NULL )
        {
        }

        template <class Comparable>
        BinarySearchTree<Comparable>::
        BinarySearchTree( const BinarySearchTree<Comparable> & rhs ) :
          root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
        { 
            *this = rhs;
        }

        template <class Comparable>
        BinarySearchTree<Comparable>::~BinarySearchTree( )
        {
            makeEmpty( );
        }

        template <class Comparable>
        void BinarySearchTree<Comparable>::insert( const Comparable & x )
        {
            insert( x, root );
        }

        template <class Comparable>
        void BinarySearchTree<Comparable>::remove( const Comparable & x )
        {
            remove( x, root );
        }


        template <class Comparable>
        Comparable BinarySearchTree<Comparable>::findMin( ) const
        {
            return elementAt( findMin( root ) );
        }

        template <class Comparable>
        Comparable BinarySearchTree<Comparable>::findMax( ) const
        {
            return elementAt( findMax( root ) );
        }

        template <class Comparable>
        Comparable BinarySearchTree<Comparable>::
                                 find( const Comparable & x ) const
        {
            return elementAt( find( x, root ) );
        }

        template <class Comparable>
        void BinarySearchTree<Comparable>::makeEmpty( )
        {
            makeEmpty( root );
        }

        template <class Comparable>
        bool BinarySearchTree<Comparable>::isEmpty( ) const
        {
            return root == NULL;
        }

        // Call to printTree from client -- Acts as a Stub for Private Call 
	//                                  Which Uses Root Ptr 

        template <class Comparable>
        void BinarySearchTree<Comparable>::printTree( ) const
        {
            if( isEmpty( ) )
                cout << "Empty tree" << endl;
            else
                printTree( root );
        }

        // Call to printTree from private --  Accesses the Root Ptr 

        template <class Comparable>
        void BinarySearchTree<Comparable>::printTree( BinaryNode<Comparable> *t ) const
        {
            if( t != NULL )
            {
                printTree( t->left );
                cout << t->element << endl;
                printTree( t->right );
            }
        }

        // Call to postOrder from client -- Acts as a Stub for Private Call 
	//                                  Which Uses Root Ptr 
	
        void BinarySearchTree<Comparable>::postOrder( ) const
        {
		if(isEmpty())
		{
			cout << "Tree is empty" << endl;
		}
		else
		{
			postOrder(root);
		}
        }

        // Call to postOrder from private -- Accesses the Root Ptr 

        template <class Comparable>
        void BinarySearchTree<Comparable>::postOrder( BinaryNode<Comparable> *t ) const
        {
		postOrder(t -> left);
		postOrder(t -> right);
		cout << t -> element << endl;
        }

        // Call to height from client -- Acts as a Stub for Private Call 
	      // Which Uses Root Ptr 


        template <class Comparable>
        int BinarySearchTree<Comparable>::height( ) const
        {
        	if(isEmpty())
		{
			cout << "Tree is empty" << endl;
		}
		else
		{
			height(root);
		}
        }


        // Call to height from private -- Accesses the Root Ptr 


       template <class Comparable>
       int BinarySearchTree<Comparable>::height ( BinaryNode<Comparable> *t ) const
       {
        	if(t == NULL)
		{
			return -1;
		}
		else
		{
			int leftHeight = height(t->left) + 1;
			int rightHeight = height(t -> right) + 1;
			if(leftHeight > rightHeight)
				return leftHeight;
			else
				return rightHeight;
		}
       }
       
       
       // Call to numLeaves from client -- Acts as a Stub for Private Call 
	      // Which Uses Root Ptr 



        template <class Comparable>
        int BinarySearchTree<Comparable>::numLeaves( ) const
        {
        	if(isEmpty())
			cout << "Tree is empty" << endl;
		else
			numLeaves(root);
        }


        // Call to numLeaves from private -- Accesses the Root Ptr 


       template <class Comparable>
       int BinarySearchTree<Comparable>::numLeaves ( BinaryNode<Comparable> *t ) const
       {
        	if (t == NULL)
			return -1;
		else
		{
			return (1 + numLeaves(t -> left) + numLeaves(t -> right));
		}
       }
       
       
       // Call to isBalanced from client -- Acts as a Stub for Private Call 
	      // Which Uses Root Ptr 



        template <class Comparable>
        bool BinarySearchTree<Comparable>::isBalanced( ) const
        {
        	if (isEmpty())
			cout << "Tree is empty" << endl;
		else
			isBalanced(root);
        }


        // Call to isBalanced from private -- Accesses the Root Ptr 


       template <class Comparable>
       bool BinarySearchTree<Comparable>::isBalanced ( BinaryNode<Comparable> *t ) const
       {
        	if (t == NULL)
			return -1;
		else
		{
			int leftHeight = height(t -> left);
			int rightHeight = height(t -> right);
			if (((leftHeight - rightHeight) <= 1) && isBalanced(t -> right) && isBalanced(t -> left))
				return true;
			else
				return false;
		}
       }

			 
        template <class Comparable>
        const BinarySearchTree<Comparable> &
        BinarySearchTree<Comparable>::
        operator=( const BinarySearchTree<Comparable> & rhs )
        {
            if( this != &rhs )
            {
                makeEmpty( );
                root = clone( rhs.root );
            }
            return *this;
        }

        template <class Comparable>
        Comparable & BinarySearchTree<Comparable>::
        elementAt( BinaryNode<Comparable> *t ) const
        {
            return t == NULL ? ITEM_NOT_FOUND : t->element;
        }

        template <class Comparable>
        void BinarySearchTree<Comparable>::
        insert( const Comparable & x, BinaryNode<Comparable> * & t ) const
        {
            if( t == NULL )
                t = new BinaryNode<Comparable>( x, NULL, NULL );
            else if( x < t->element )
                insert( x, t->left );
            else if( t->element < x )
                insert( x, t->right );
            else
                ;  // Duplicate; do nothing
        }

        template <class Comparable>
        void BinarySearchTree<Comparable>::
        remove( const Comparable & x, BinaryNode<Comparable> * & t ) const
        {
            if( t == NULL )
                return;   // Item not found; do nothing
            if( x < t->element )
                remove( x, t->left );
            else if( t->element < x )
                remove( x, t->right );
            else if( t->left != NULL && t->right != NULL ) // Two children
            {
                t->element = findMin( t->right )->element;
                remove( t->element, t->right );
            }
            else
            {
                BinaryNode<Comparable> *oldNode = t;
                t = ( t->left != NULL ) ? t->left : t->right;
                delete oldNode;
            }
        }

        template <class Comparable>
        BinaryNode<Comparable> *
        BinarySearchTree<Comparable>::findMin( BinaryNode<Comparable> *t ) const
        {
            if( t == NULL )
                return NULL;
            if( t->left == NULL )
                return t;
            return findMin( t->left );
        }

        template <class Comparable>
        BinaryNode<Comparable> *
        BinarySearchTree<Comparable>::findMax( BinaryNode<Comparable> *t ) const
        {
            if( t != NULL )
                while( t->right != NULL )
                    t = t->right;
            return t;
        }

        template <class Comparable>
        BinaryNode<Comparable> *
        BinarySearchTree<Comparable>::
        find( const Comparable & x, BinaryNode<Comparable> *t ) const
        {
            if( t == NULL )
                return NULL;
            else if( x < t->element )
                return find( x, t->left );
            else if( t->element < x )
                return find( x, t->right );
            else
                return t;    // Match
        }

        template <class Comparable>
        void BinarySearchTree<Comparable>::
        makeEmpty( BinaryNode<Comparable> * & t ) const
        {
            if( t != NULL )
            {
                makeEmpty( t->left );
                makeEmpty( t->right );
                delete t;
            }
            t = NULL;
        }

        template <class Comparable>
        BinaryNode<Comparable> *
        BinarySearchTree<Comparable>::clone( BinaryNode<Comparable> * t ) const
        {
            if( t == NULL )
                return NULL;
            else
                return new BinaryNode<Comparable>( t->element, clone( t->left ), clone( t->right ) );
        }

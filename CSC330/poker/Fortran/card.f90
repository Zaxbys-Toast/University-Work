module DeckModule
    implicit none

    type :: Card
        character(len=2) :: rank
        character(len=1) :: suit
    contains
        procedure :: initializeCard
        procedure :: displayCard
    end type Card

contains

    ! Initialize a Card from a string representation
    subroutine initializeCard(this, cardStr)
        class(Card), intent(inout) :: this
        character(len=*), intent(in) :: cardStr

        this%rank = cardStr(1:2)
        this%suit = cardStr(3:3)
    end subroutine initializeCard

    ! Display the card
    subroutine displayCard(this)
        class(Card), intent(in) :: this
        print *, "Card: ", trim(this%rank), " of ", trim(this%suit)
    end subroutine displayCard

    type :: Deck
        type(Card), allocatable :: cards(:)
        integer :: size
    end type Deck

    ! Other subroutines like shuffle, dealCard, and readHandsFromFile

end module DeckModule


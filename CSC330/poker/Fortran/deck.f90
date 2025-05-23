module DeckModule
    implicit none

    type :: Card
        character(len=2) :: rank
        character(len=1) :: suit
    contains
        procedure :: initializeCard
        procedure :: displayCard
    end type Card

    type :: Deck
        type(Card), allocatable :: cards(:)
        integer :: size
    contains
        procedure :: initializeDeck
        procedure :: shuffle
        procedure :: deal
    end type Deck

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

    ! Initialize the Deck with all 52 cards
    subroutine initializeDeck(this)
        class(Deck), intent(inout) :: this
        character(len=2), dimension(13) :: ranks
        character(len=1), dimension(4) :: suits
        integer :: i, j, index

        ranks = [ '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' ]
        suits = [ 'H', 'D', 'C', 'S' ]
        this%size = 0
        allocate(this%cards(52))  ! 52 cards in a standard deck

        index = 1
        do i = 1, size(ranks)
            do j = 1, size(suits)
                call this%cards(index)%initializeCard(trim(ranks(i) // suits(j)))
                index = index + 1
            end do
        end do
        this%size = index - 1  ! Update size to the number of cards
    end subroutine initializeDeck

    ! Shuffle the Deck using the Fisher-Yates algorithm
    subroutine shuffle(this)
        class(Deck), intent(inout) :: this
        integer :: i, j
        type(Card) :: temp

        do i = this%size, 2, -1
            call random_number(j)
            j = 1 + floor(j * i)
            temp = this%cards(i)
            this%cards(i) = this%cards(j)
            this%cards(j) = temp
        end do
    end subroutine shuffle

    ! Deal a card from the Deck
    function deal(this) result(card)
        class(Deck), intent(inout) :: this
        type(Card) :: card

        if (this%size == 0) then
            print *, "No cards left to deal!"
            stop
        end if

        card = this%cards(this%size)  ! Get the top card
        this%size = this%size - 1  ! Decrease the size
    end function deal

end module DeckModule


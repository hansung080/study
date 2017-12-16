package main

import (
	"fmt"
)

// NewFibonacciGenerator1 creates a fibonacci generator and is implemented with closure. 
func NewFibonacciGenerator1(max int) func() int {
	next, a, b := 0, 0, 1
	return func() int {
		next, a, b = a, b, a+b
		if next > max {
			return -1
		}

		return next
	}
}

// NewFibonacciGenerator2 creates a fibonacci generator and is implemented with channel. 
func NewFibonacciGenerator2(max int) <-chan int {
	c := make(chan int)

	go func() {
		defer close(c)
		a, b := 0, 1
		for a <= max {
			c <- a
			a, b = b, a+b
		}
	}()

	return c
}

func main() {
	fmt.Printf("fibonacci with closure: ")
	fib := NewFibonacciGenerator1(15)
	for i := fib(); i >= 0; i = fib() {
		fmt.Printf("%d, ", i)
	}
	fmt.Println()

	fmt.Printf("fibonacci with channel: ")
	for i := range NewFibonacciGenerator2(15) {
		fmt.Printf("%d, ", i)	
	}
	fmt.Println()	
}

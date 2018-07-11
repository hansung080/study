package main

import (
	"fmt"
)

// NewIntGenerator1 creates a integer generator and is implemented with closure. 
func NewIntGenerator1(max int) func() int {
	next := -1
	return func() int {
		next++
		if next > max {
			return -1
		}

		return next
	}
}

// NewIntGenerator2 creates a integer generator and is implemented with channel. 
func NewIntGenerator2(max int) <-chan int {
	c := make(chan int)

	go func() {
		defer close(c)
		next := 0
		for next <= max {
			c <- next
			next++
		}
	}()

	return c
}


func main() {
	fmt.Println("===== integer generator with closure =====")
	gen1 := NewIntGenerator1(5)
	for i := gen1(); i >= 0; i = gen1() {
		fmt.Println(i)
	}

	fmt.Println("===== integer generator with channel =====")
	for i := range NewIntGenerator2(5) {
		fmt.Println(i)
	}
}

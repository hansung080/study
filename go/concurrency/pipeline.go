package main

import (
	"fmt"
)

func PlusOne(in <-chan int) <-chan int {
	out := make(chan int)
	go func() {
		defer close(out)
		for num := range in {
			out <- num + 1
		}
	}()

	return out
}

type IntPipe func(<-chan int) <-chan int

func Chain(pipes ...IntPipe) IntPipe {
	return func(in <-chan int) <-chan int {
		c := in
		for _, pipe := range pipes {
			c = pipe(c)
		}

		return c
	}
}

func main() {
	c := make(chan int)
	go func() {
		defer close(c)
		c <- 100
		c <- 200
		c <- 300
	}()

	fmt.Println("==== plus two ====")
	for num := range PlusOne(PlusOne(c)) {
		fmt.Println(num)
	}

	c2 := make(chan int)
	go func() {
		defer close(c2)
		c2 <- 100
		c2 <- 200
		c2 <- 300
	}()

	fmt.Println("==== plus two with chain ====")
	PlusTwo := Chain(PlusOne, PlusOne)
	for num := range PlusTwo(c2) {
		fmt.Println(num)
	}
}

package main

import (
	"fmt"
)

func main() {
	c := func() <-chan int {
		c := make(chan int)
		go func() {
			defer close(c)
			c <- 1
			c <- 2
			c <- 3
		}()

		return c
	}()

	for val := range c {
		fmt.Println(val)
	}
}

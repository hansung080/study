package main

import (
	"fmt"
	"time"
)

func main() {
	c := func() <-chan int{
		c := make(chan int)
		go func() {
			time.Sleep(1500 * time.Millisecond)
			c <- 100
		}()

		return c
	}()

	var num int
	select {
	case num = <-c:
	case <-time.After(2 * time.Second):
		num = 0
	}

	fmt.Println(num)
}

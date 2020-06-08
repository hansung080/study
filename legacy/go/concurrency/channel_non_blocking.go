package main

import (
	"fmt"
	"time"
)

func main() {
	c := func() <-chan int {
		c := make(chan int)
		go func() {
			//c <- 100
		}()

		return c
	}()

	time.Sleep(100 * time.Millisecond)

	var num int
	select {
	case num = <-c:
	default:
		num = 0
	}

	fmt.Println(num)
}

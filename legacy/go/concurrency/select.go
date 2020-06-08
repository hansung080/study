package main

import (
	"fmt"
	"time"
)

func send() int {
	fmt.Printf("always called. ")
	return 300
}	

func main() {
	c1 := make(chan int)
	c2 := make(chan int)
	c3 := make(chan int)
	c4 := make(chan int)

	go func() {
		time.Sleep(3 * time.Second)
		c1 <- 100
	} ()

	go func() {
		time.Sleep(6 * time.Second)
		c2 <- 200
	} ()

	go func() {
		time.Sleep(9 * time.Second)
		fmt.Printf("%d is from c3.\n", <-c3)
	} ()

	go func() {
		time.Sleep(12 * time.Second)
		c4 <- 400
	}()

	stop := false
	for {	
		select {
		case n := <-c1:
			fmt.Printf("%d is from c1.\n", n)

		case n := <-c2:
			fmt.Printf("%d is from c2.\n", n)

		case c3 <- send():
			fmt.Printf("send to c3. ")

		case n := <-c4:
			fmt.Printf("%d is from c4.\n", n)
			stop = true

		default:
			fmt.Println("no channels are ready.")
		}

		if stop {
			break
		}

		time.Sleep(time.Second)
	}
}

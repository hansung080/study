package main

import (
	"fmt"
)

func FanIn3(in1, in2, in3 <-chan int) <-chan int {
	out := make(chan int)

	openCnt := 3
	closeChan := func(c *<-chan int) bool {
		*c = nil
		openCnt--
		return openCnt == 0
	}

	go func() {
		defer close(out)
		for {
			select {
			case num, ok := <-in1:
				if ok {
					out <- num
				} else if closeChan(&in1) {
					return
				}

			case num, ok := <-in2:
				if ok {
					out <- num
				} else if closeChan(&in2) {
					return
				}

			case num, ok := <-in3:
				if ok {
					out <- num
				} else if closeChan(&in3) {
					return
				}				
			}
		}
	}()

	return out
}

func main() {
	in1, in2, in3 := make(chan int), make(chan int), make(chan int)
	send := func(c chan<- int, begin, end int) {
		defer close(c)
		for i := begin; i < end; i++ {
			c <- i
		}
	}

	go send(in1, 100, 105)
	go send(in2, 200, 205)
	go send(in3, 300, 305)

	for num := range FanIn3(in1, in2, in3) {
		fmt.Println(num)
	}
}

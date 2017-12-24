package main

import (
	"fmt"
	"sync"
)

type Request struct {
	Num  int
	Resp chan Response
}

type Response struct {
	Num      int
	WorkerID int
}

func PlusOneService(reqs chan Request, workerID int) {
	for req := range reqs {
		go func(req Request) {
			defer close(req.Resp)
			req.Resp <- Response{
				Num:      req.Num + 1,
				WorkerID: workerID,
			}
		}(req)
	}
}

func main() {
	reqs := make(chan Request)
	defer close(reqs)
	for i := 0; i < 3; i++ {
		go PlusOneService(reqs, i)
	}

	var wg sync.WaitGroup
	for num := 3; num < 53; num += 10 {
		wg.Add(1)
		go func(num int) {
			defer wg.Done()
			resps := make(chan Response)
			reqs <- Request{
				Num:  num,
				Resp: resps,
			}
			fmt.Println(num, "->", <-resps)
		}(num)
	}

	wg.Wait()
}

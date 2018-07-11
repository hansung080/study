// Binary fileserver is a file server example.
// Put the command below to run file server.
// -> go run fileserver.go --addr=localhost:8888 --root=$GOPATH/src/github.com/hansung080/taskman_server/net/http/taskman
package main

import (
	"flag"
	"log"
	"net/http"
)

var (
	addr = flag.String(
		"addr",
		":8888",
		"address of the webserver",
	)

	root = flag.String(
		"root",
		"/Users/hansung/Documents/work/ws/go/src/github.com/hansung080/taskman_server/net/http/taskman",
		"root directory",
	)
)

func main() {
	flag.Parse()
	log.Fatal(http.ListenAndServe(
		*addr,
		http.FileServer(http.Dir(*root)),
	))
}

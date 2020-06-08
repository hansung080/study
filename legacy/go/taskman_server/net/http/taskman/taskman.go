/**
 * REST란? REpresentational State Transfer의 약어
 *
 * 1. 구성 요소
 *   - 자원(Resource) : URI
 *   - 행위(Verb)     : HTTP Method
 *   - 표현(Representation)
 *
 * 2. HTTP Method
 *   - GET    : Select
 *   - POST   : Insert
 *   - PUT    : Update
 *   - DELETE : Delete
 */

package main

import (
	"log"
	"net/http"

	"github.com/gorilla/mux"
)

const (
	apiPathPrefix  = "/api/v1/task/"
	htmlPathPrefix = "/task/"
	idPattern      = "/{id:[0-9a-f]+}"
)

func main() {
	r := mux.NewRouter()
	r.PathPrefix(htmlPathPrefix).Path(idPattern).Methods("GET").HandlerFunc(htmlHandler)

	s := r.PathPrefix(apiPathPrefix).Subrouter()
	s.HandleFunc(idPattern, apiGetHandler).Methods("GET")
	s.HandleFunc("/", apiPostHandler).Methods("POST")
	s.HandleFunc(idPattern, apiPutHandler).Methods("PUT")
	s.HandleFunc(idPattern, apiDeleteHandler).Methods("DELETE")

	http.Handle("/", r)
	http.Handle("/css/", http.StripPrefix("/css/", http.FileServer(http.Dir("cssfiles"))))
	log.Fatal(http.ListenAndServe(":8888", nil))
}

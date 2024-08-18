package tools

import (
	"html/template"
	"net/http"

	"github.com/gorilla/mux"
)

// Portal represents the developer portal
type Portal struct {
	logger log.Logger
}

// NewPortal returns a new instance of Portal
func NewPortal(logger log.Logger) *Portal {
	return &Portal{
		logger: logger,
	}
}

// ServeHTTP serves the portal
func (p *Portal) ServeHTTP(w http.ResponseWriter, req *http.Request) {
	// Create a new router
	r := mux.NewRouter()

	// Register routes
	r.Handle("/", p.indexHandler).Methods("GET")
	r.Handle("/docs", p.docsHandler).Methods("GET")
	r.Handle("/tutorials", p.tutorialsHandler).Methods("GET")
	r.Handle("/resources", p.resourcesHandler).Methods("GET")

	// Serve the portal
	http.Handle("/", r)
}

func (p *Portal) indexHandler(w http.ResponseWriter, req *http.Request) {
	t, err := template.New("index").ParseFiles("templates/index.html")
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	t.Execute(w, nil)
}

func (p *Portal) docsHandler(w http.ResponseWriter, req *http.Request) {
	t, err := template.New("docs").ParseFiles("templates/docs.html")
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	t.Execute(w, nil)
}

func (p *Portal) tutorialsHandler(w http.ResponseWriter, req *http.Request) {
	t, err := template.New("tutorials").ParseFiles("templates/tutorials.html")
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	t.Execute(w, nil)
}

func (p *Portal) resourcesHandler(w http.ResponseWriter, req *http.Request) {
	t, err := template.New("resources").ParseFiles("templates/resources.html")
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	t.Execute(w, nil)
}

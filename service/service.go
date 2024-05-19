package service

import (
	"html/template"
	"io"
	"net/http"

	"github.com/amrojjeh/tictactoe/ui"
	"github.com/labstack/echo/v4"
	"github.com/labstack/echo/v4/middleware"
	"nhooyr.io/websocket"
)

func StartServer(addr string) {
	e := echo.New()
	e.Use(middleware.Recover())
	e.Use(middleware.Logger())
	p := &page{
		templates: template.Must(template.ParseFS(ui.Files, "*.html")),
	}
	e.Renderer = p
	e.StaticFS("/static", ui.Files)
	e.GET("/", index)
	e.GET("/ws", initWS)
	e.Logger.Fatal(e.Start(addr))
}

func index(c echo.Context) error {
	return c.Render(http.StatusOK, "index", nil)
}

func initWS(c echo.Context) error {
	_, err := websocket.Accept(c.Response().Writer, c.Request(), nil)
	if err != nil {
		return err
	}
	return nil
}

type page struct {
	templates *template.Template
}

func (t *page) Render(w io.Writer, name string, data interface{}, c echo.Context) error {
	return t.templates.ExecuteTemplate(w, name, data)
}

package analytics

import (
	"context"
	"fmt"
	"net/http"

	"github.com/prometheus/client_golang/prometheus"
	"github.com/prometheus/client_golang/prometheus/promhttp"
)

// MonitoringClient represents a monitoring client
type MonitoringClient struct {
	prometheus *prometheus.Client
}

// NewMonitoringClient returns a new instance of MonitoringClient
func NewMonitoringClient() (*MonitoringClient, error) {
	prometheusClient, err := prometheus.NewClient()
	if err != nil {
		return nil, err
	}

	return &MonitoringClient{
		prometheus: prometheusClient,
	}, nil
}

// StartServer starts the Prometheus server
func (mc *MonitoringClient) StartServer(addr string) error {
	http.Handle("/metrics", promhttp.Handler())
	return http.ListenAndServe(addr, nil)
}

// RegisterMetric registers a metric
func (mc *MonitoringClient) RegisterMetric(metric *prometheus.GaugeVec) error {
	return mc.prometheus.Register(metric)
}

// Incr increments a metric
func (mc *MonitoringClient) Incr(metric *prometheus.GaugeVec, labels prometheus.Label

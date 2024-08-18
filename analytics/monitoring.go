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
func (mc *MonitoringClient) Incr(metric *prometheus.GaugeVec, labels prometheus.Labels) {
	metric.With(labels).Inc()
}

// Decr decrements a metric
func (mc *MonitoringClient) Decr(metric *prometheus.GaugeVec, labels prometheus.Labels) {
	metric.With(labels).Dec()
}

// Set sets a metric value
func (mc *MonitoringClient) Set(metric *prometheus.GaugeVec, labels prometheus.Labels, value float64) {
	metric.With(labels).Set(value)
}

// GetMetric gets a metric value
func (mc *MonitoringClient) GetMetric(metric *prometheus.GaugeVec, labels prometheus.Labels) (float64, error) {
	return metric.With(labels).Get(), nil
}

// NewGaugeVec creates a new gauge vector
func (mc *MonitoringClient) NewGaugeVec(name string, help string, labels []string) (*prometheus.GaugeVec, error) {
	return prometheus.NewGaugeVec(prometheus.GaugeOpts{
		Name: name,
		Help: help,
	}, labels)
}

// NewCounterVec creates a new counter vector
func (mc *MonitoringClient) NewCounterVec(name string, help string, labels []string) (*prometheus.CounterVec, error) {
	return prometheus.NewCounterVec(prometheus.CounterOpts{
		Name: name,
		Help: help,
	}, labels)
}

// NewSummaryVec creates a new summary vector
func (mc *MonitoringClient) NewSummaryVec(name string, help string, labels []string, obj *prometheus.SummaryOpts) (*prometheus.SummaryVec, error) {
	return prometheus.NewSummaryVec(obj, labels)
}

// NewHistogramVec creates a new histogram vector
func (mc *MonitoringClient) NewHistogramVec(name string, help string, labels []string, obj *prometheus.HistogramOpts) (*prometheus.HistogramVec, error) {
	return prometheus.NewHistogramVec(obj, labels)
}

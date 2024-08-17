package network

import (
	"crypto/sha256"
	"encoding/json"
	"fmt"
	"log"
	"net"
	"sync"

	"github.com/nexus-chain/nexus-chain/chain"
)

// Network represents a network interface
type Network interface {
	SendMessage(message []byte) error
	ReceiveMessage() ([]byte, error)
}

// TCPNetwork represents a TCP network interface
type TCPNetwork struct {
	listener net.Listener
	conn     net.Conn
	mu       sync.Mutex
}

// NewTCPNetwork returns a new TCP network interface instance
func NewTCPNetwork(address string) (*TCPNetwork, error) {
	listener, err := net.Listen("tcp", address)
	if err != nil {
		return nil, err
	}

	return &TCPNetwork{
		listener: listener,
	}, nil
}

// SendMessage sends a message over the network
func (tn *TCPNetwork) SendMessage(message []byte) error {
	tn.mu.Lock()
	defer tn.mu.Unlock()

	if tn.conn == nil {
		return errors.New("connection not established")
	}

	_, err := tn.conn.Write(message)
	if err != nil {
		return err
	}

	return nil
}

// ReceiveMessage receives a message over the network
func (tn *TCPNetwork) ReceiveMessage() ([]byte, error) {
	tn.mu.Lock()
	defer tn.mu.Unlock()

	if tn.conn == nil {
		return nil, errors.New("connection not established")
	}

	buf := make([]byte, 1024)
	n, err := tn.conn.Read(buf)
	if err != nil {
		return nil, err
	}

	return buf[:n], nil
}

// Accept accepts incoming connections
func (tn *TCPNetwork) Accept() error {
	tn.mu.Lock()
	defer tn.mu.Unlock()

	conn, err := tn.listener.Accept()
	if err != nil {
		return err
	}

	tn.conn = conn

	return nil
}

// Close closes the network connection
func (tn *TCPNetwork) Close() error {
	tn.mu.Lock()
	defer tn.mu.Unlock()

	if tn.conn != nil {
		err := tn.conn.Close()
		if err != nil {
			return err
		}
	}

	err := tn.listener.Close()
	if err != nil {
		return err
	}

	return nil
}

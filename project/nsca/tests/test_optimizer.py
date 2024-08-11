import unittest
from optimizer import Optimizer
from contract import Contract
from data_loader import DataLoader

class TestOptimizer(unittest.TestCase):
    def setUp(self):
        self.data_loader = DataLoader('data/training_data/contracts.csv')
        self.contract = Contract('contract_code.sol', self.data_loader)
        self.optimizer = Optimizer(self.contract)

    def test_optimize_contract(self):
        optimized_contract = self.optimizer.optimize_contract()
        self.assertIsInstance(optimized_contract, Contract)
        self.assertNotEqual(optimized_contract.code, self.contract.code)

    def test_get_optimized_code(self):
        optimized_code = self.optimizer.get_optimized_code()
        self.assertIsInstance(optimized_code, str)
        self.assertGreater(len(optimized_code), 0)

    def test_get_gas_savings(self):
        gas_savings = self.optimizer.get_gas_savings()
        self.assertIsInstance(gas_savings, float)
        self.assertGreaterEqual(gas_savings, 0.0)

    def test_get_execution_time_savings(self):
        execution_time_savings = self.optimizer.get_execution_time_savings()
        self.assertIsInstance(execution_time_savings, float)
        self.assertGreaterEqual(execution_time_savings, 0.0)

    def test_optimize_contract_with_analysis(self):
        optimized_contract = self.optimizer.optimize_contract_with_analysis()
        self.assertIsInstance(optimized_contract, Contract)
        self.assertNotEqual(optimized_contract.code, self.contract.code)

if __name__ == '__main__':
    unittest.main()

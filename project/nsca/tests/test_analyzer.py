import unittest
from analyzer import Analyzer
from contract import Contract
from data_loader import DataLoader

class TestAnalyzer(unittest.TestCase):
    def setUp(self):
        self.data_loader = DataLoader('data/training_data/contracts.csv')
        self.contract = Contract('contract_code.sol', self.data_loader)
        self.analyzer = Analyzer(self.contract)

    def test_analyze_contract(self):
        result = self.analyzer.analyze_contract()
        self.assertIsInstance(result, dict)
        self.assertIn('complexity', result)
        self.assertIn('security_vulnerabilities', result)
        self.assertIn('performance_issues', result)

    def test_get_complexity(self):
        complexity = self.analyzer.get_complexity()
        self.assertIsInstance(complexity, int)
        self.assertGreaterEqual(complexity, 0)

    def test_get_security_vulnerabilities(self):
        vulnerabilities = self.analyzer.get_security_vulnerabilities()
        self.assertIsInstance(vulnerabilities, list)
        self.assertGreaterEqual(len(vulnerabilities), 0)

    def test_get_performance_issues(self):
        issues = self.analyzer.get_performance_issues()
        self.assertIsInstance(issues, list)
        self.assertGreaterEqual(len(issues), 0)

    def test_get_recommendations(self):
        recommendations = self.analyzer.get_recommendations()
        self.assertIsInstance(recommendations, list)
        self.assertGreaterEqual(len(recommendations), 0)

    def test_analyze_contract_with_optimization(self):
        optimized_contract = self.analyzer.analyze_contract_with_optimization()
        self.assertIsInstance(optimized_contract, Contract)
        self.assertNotEqual(optimized_contract.code, self.contract.code)

if __name__ == '__main__':
    unittest.main()

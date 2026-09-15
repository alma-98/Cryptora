export interface DashboardWallet {
  address: string;
  label: string;
  active: boolean;
  asset?: string;
  balance?: string;
}

export interface DashboardTransaction {
  transactionId: string;
  from: string;
  to: string;
  asset: string;
  amount: string;
  tenor: string;
  status: string;
  blockNumber?: string;
}

const RPC_URL =
  import.meta.env.VITE_CRYPTORA_RPC_URL ||
  "http://127.0.0.1:8545";

export interface NativeWallet {
  address: string;
  label: string;
  active: boolean;
  asset?: string;
  balance?: string;
}

export interface NativeTransaction {
  transactionId?: string;
  hash?: string;
  from: string;
  to: string;
  asset: string;
  amount?: string;
  value?: string;
  tenor: string;
  status: string;
  blockNumber?: string;
}

async function rpc(
  method: string,
  params: Record<string, string> = {}
) {
  const response = await fetch(RPC_URL, {
    method: "POST",
    headers: {
      "Content-Type": "application/json"
    },
    body: JSON.stringify({
      jsonrpc: "2.0",
      id: Date.now(),
      method,
      params
    })
  });

  if (!response.ok) {
    throw new Error(
      `Cryptora RPC HTTP ${response.status}`
    );
  }

  const data = await response.json();

  if (data.error) {
    throw new Error(
      data.error.message ||
      "Cryptora RPC request failed"
    );
  }

  return data.result;
}

export async function getWallets(): Promise<NativeWallet[]> {
  const response = await fetch(
    `${RPC_URL}/wallets`
  );

  if (!response.ok) {
    throw new Error("Failed to load wallets");
  }

  const data = await response.json();

  return data.wallets || [];
}

export async function getWallet(
  address: string
): Promise<NativeWallet> {

  const response = await fetch(
    `${RPC_URL}/wallet/${encodeURIComponent(address)}`
  );

  if (!response.ok) {
    throw new Error("Failed to load wallet");
  }

  return response.json();
}

export async function createWallet(
  address: string,
  label: string
): Promise<NativeWallet> {

  return rpc(
    "cryptora_createWallet",
    {
      address,
      label
    }
  );
}

export async function updateWallet(
  address: string,
  label: string,
  active: boolean
): Promise<boolean> {

  return rpc(
    "cryptora_updateWallet",
    {
      address,
      label,
      active: active ? "true" : "false"
    }
  );
}

export async function deleteWallet(
  address: string
): Promise<boolean> {

  return rpc(
    "cryptora_deleteWallet",
    {
      address
    }
  );
}

export async function sendTransaction(
  from: string,
  to: string,
  amount: string,
  tenor: string
): Promise<string> {

  return rpc(
    "cryptora_sendTransaction",
    {
      from,
      to,
      asset: "CRC",
      amount,
      tenor
    }
  );
}

export async function getTransaction(
  transactionId: string
): Promise<NativeTransaction | null> {

  return rpc(
    "cryptora_getTransaction",
    {
      transactionId
    }
  );
}

export async function getTransactionByHash(
  hash: string
): Promise<NativeTransaction | null> {

  return rpc(
    "eth_getTransactionByHash",
    {
      hash
    }
  );
}

export async function getTransactionReceipt(
  hash: string
) {

  return rpc(
    "eth_getTransactionReceipt",
    {
      hash
    }
  );
}

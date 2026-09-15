import {
  useCallback,
  useEffect,
  useMemo,
  useState
} from "react";

import {
  createWallet,
  getWallets,
  getTransactionByHash,
  sendTransaction
} from "../services/cryptoraNative";

import type {
  DashboardWallet,
  DashboardTransaction
} from "../types/cryptora";

export default function NativeDashboard() {

  const [wallets, setWallets] =
    useState<DashboardWallet[]>([]);

  const [selectedWallet, setSelectedWallet] =
    useState("");

  const [from, setFrom] =
    useState("CRYPTORA_GENESIS");

  const [to, setTo] =
    useState("");

  const [amount, setAmount] =
    useState("25");

  const [tenor, setTenor] =
    useState("30D");

  const [label, setLabel] =
    useState("");

  const [newAddress, setNewAddress] =
    useState("");

  const [transaction, setTransaction] =
    useState<DashboardTransaction | null>(null);

  const [loading, setLoading] =
    useState(false);

  const [message, setMessage] =
    useState("");

  const [error, setError] =
    useState("");

  const loadWallets = useCallback(
    async () => {

      try {

        const result =
          await getWallets();

        setWallets(result);

      } catch (err) {

        setError(
          err instanceof Error
            ? err.message
            : "Failed to load wallets"
        );
      }
    },
    []
  );

  useEffect(() => {
    loadWallets();

    const interval =
      window.setInterval(
        loadWallets,
        5000
      );

    return () =>
      window.clearInterval(interval);

  }, [loadWallets]);

  const totalBalance = useMemo(() => {

    return wallets.reduce(
      (total, wallet) =>
        total +
        Number(wallet.balance || 0),
      0
    );

  }, [wallets]);

  async function handleCreateWallet() {

    setError("");
    setMessage("");

    if (!newAddress.trim()) {
      setError(
        "Wallet address wajib diisi."
      );
      return;
    }

    try {

      setLoading(true);

      await createWallet(
        newAddress.trim(),
        label.trim()
      );

      setMessage(
        "Wallet berhasil dibuat."
      );

      setNewAddress("");
      setLabel("");

      await loadWallets();

    } catch (err) {

      setError(
        err instanceof Error
          ? err.message
          : "Create wallet failed"
      );

    } finally {
      setLoading(false);
    }
  }

  async function handleSend() {

    setError("");
    setMessage("");
    setTransaction(null);

    if (!from || !to || !amount || !tenor) {
      setError(
        "From, destination, amount, dan tenor wajib diisi."
      );
      return;
    }

    try {

      setLoading(true);

      const txid =
        await sendTransaction(
          from,
          to,
          amount,
          tenor
        );

      setMessage(
        `Transaction confirmed: ${txid}`
      );

      const result =
        await getTransactionByHash(
          txid
        );

      if (result) {

        setTransaction({
          transactionId:
            result.hash || txid,
          from: result.from,
          to: result.to,
          asset:
            result.asset || "CRC",
          amount:
            result.value || "0",
          tenor: result.tenor,
          status:
            result.status,
          blockNumber:
            result.blockNumber
        });
      }

      await loadWallets();

    } catch (err) {

      setError(
        err instanceof Error
          ? err.message
          : "Transaction failed"
      );

    } finally {
      setLoading(false);
    }
  }

  return (
    <main
      style={{
        minHeight: "100vh",
        padding: "32px",
        background: "#f8fafc",
        fontFamily:
          "Inter, system-ui, sans-serif"
      }}
    >

      <section
        style={{
          maxWidth: "1400px",
          margin: "0 auto"
        }}
      >

        <header
          style={{
            marginBottom: "28px"
          }}
        >
          <p
            style={{
              margin: 0,
              color: "#2563eb",
              fontWeight: 700
            }}
          >
            CRYPTORA NATIVE BLOCKCHAIN
          </p>

          <h1
            style={{
              margin: "6px 0",
              fontSize: "32px"
            }}
          >
            Native Wallet Dashboard
          </h1>

          <p
            style={{
              color: "#64748b"
            }}
          >
            Native CRC transaction control
            connected directly to Cryptora Node.
          </p>
        </header>

        {message && (
          <div
            style={{
              padding: "14px",
              marginBottom: "16px",
              background: "#dcfce7",
              borderRadius: "10px"
            }}
          >
            {message}
          </div>
        )}

        {error && (
          <div
            style={{
              padding: "14px",
              marginBottom: "16px",
              background: "#fee2e2",
              color: "#991b1b",
              borderRadius: "10px"
            }}
          >
            {error}
          </div>
        )}

        <div
          style={{
            display: "grid",
            gridTemplateColumns:
              "repeat(auto-fit,minmax(220px,1fr))",
            gap: "16px",
            marginBottom: "24px"
          }}
        >

          <div
            style={{
              background: "white",
              padding: "22px",
              borderRadius: "14px"
            }}
          >
            <small>Total Wallets</small>
            <h2>{wallets.length}</h2>
          </div>

          <div
            style={{
              background: "white",
              padding: "22px",
              borderRadius: "14px"
            }}
          >
            <small>Total CRC Balance</small>
            <h2>
              {totalBalance.toFixed(6)}
            </h2>
          </div>

          <div
            style={{
              background: "white",
              padding: "22px",
              borderRadius: "14px"
            }}
          >
            <small>Native Asset</small>
            <h2>CRC</h2>
          </div>

          <div
            style={{
              background: "white",
              padding: "22px",
              borderRadius: "14px"
            }}
          >
            <small>Network</small>
            <h2>Cryptora Native</h2>
          </div>

        </div>

        <div
          style={{
            display: "grid",
            gridTemplateColumns:
              "repeat(auto-fit,minmax(320px,1fr))",
            gap: "20px"
          }}
        >

          <section
            style={{
              background: "white",
              padding: "24px",
              borderRadius: "14px"
            }}
          >

            <h2>Wallet Management</h2>

            <input
              placeholder="Wallet address"
              value={newAddress}
              onChange={e =>
                setNewAddress(e.target.value)
              }
              style={{
                width: "100%",
                padding: "12px",
                marginBottom: "10px",
                boxSizing: "border-box"
              }}
            />

            <input
              placeholder="Wallet label"
              value={label}
              onChange={e =>
                setLabel(e.target.value)
              }
              style={{
                width: "100%",
                padding: "12px",
                marginBottom: "12px",
                boxSizing: "border-box"
              }}
            />

            <button
              onClick={handleCreateWallet}
              disabled={loading}
              style={{
                width: "100%",
                padding: "12px",
                cursor: "pointer"
              }}
            >
              Create Wallet
            </button>

            <hr />

            <h3>Registered Wallets</h3>

            {wallets.map(wallet => (

              <div
                key={wallet.address}
                style={{
                  padding: "12px 0",
                  borderBottom:
                    "1px solid #e2e8f0"
                }}
              >

                <strong>
                  {wallet.label ||
                    "Unnamed Wallet"}
                </strong>

                <div
                  style={{
                    fontSize: "12px",
                    wordBreak:
                      "break-all"
                  }}
                >
                  {wallet.address}
                </div>

                <div>
                  {wallet.balance || "0.000000"} CRC
                </div>

                <span>
                  {wallet.active
                    ? "ACTIVE"
                    : "INACTIVE"}
                </span>

              </div>

            ))}

          </section>

          <section
            style={{
              background: "white",
              padding: "24px",
              borderRadius: "14px"
            }}
          >

            <h2>Send Native CRC</h2>

            <label>From</label>

            <input
              value={from}
              onChange={e =>
                setFrom(e.target.value)
              }
              style={{
                width: "100%",
                padding: "12px",
                margin: "8px 0 14px",
                boxSizing: "border-box"
              }}
            />

            <label>Destination Wallet</label>

            <select
              value={selectedWallet}
              onChange={e => {
                setSelectedWallet(
                  e.target.value
                );
                setTo(e.target.value);
              }}
              style={{
                width: "100%",
                padding: "12px",
                margin: "8px 0 14px"
              }}
            >
              <option value="">
                Select registered wallet
              </option>

              {wallets
                .filter(wallet =>
                  wallet.active
                )
                .map(wallet => (
                  <option
                    key={wallet.address}
                    value={wallet.address}
                  >
                    {wallet.label ||
                      wallet.address}
                  </option>
                ))}
            </select>

            <input
              placeholder="Destination address"
              value={to}
              onChange={e =>
                setTo(e.target.value)
              }
              style={{
                width: "100%",
                padding: "12px",
                marginBottom: "14px",
                boxSizing: "border-box"
              }}
            />

            <label>Amount CRC</label>

            <input
              value={amount}
              onChange={e =>
                setAmount(e.target.value)
              }
              type="number"
              min="0"
              step="0.000001"
              style={{
                width: "100%",
                padding: "12px",
                margin: "8px 0 14px",
                boxSizing: "border-box"
              }}
            />

            <label>Tenor</label>

            <select
              value={tenor}
              onChange={e =>
                setTenor(e.target.value)
              }
              style={{
                width: "100%",
                padding: "12px",
                margin: "8px 0 18px"
              }}
            >
              <option value="30D">
                30 Days
              </option>
              <option value="60D">
                60 Days
              </option>
              <option value="90D">
                90 Days
              </option>
            </select>

            <button
              onClick={handleSend}
              disabled={loading}
              style={{
                width: "100%",
                padding: "14px",
                cursor: "pointer"
              }}
            >
              {loading
                ? "Processing..."
                : "Send CRC"}
            </button>

          </section>

        </div>

        {transaction && (

          <section
            style={{
              background: "white",
              padding: "24px",
              borderRadius: "14px",
              marginTop: "20px"
            }}
          >

            <h2>Latest Transaction</h2>

            <p>
              <strong>TXID:</strong>{" "}
              {transaction.transactionId}
            </p>

            <p>
              <strong>From:</strong>{" "}
              {transaction.from}
            </p>

            <p>
              <strong>To:</strong>{" "}
              {transaction.to}
            </p>

            <p>
              <strong>Asset:</strong>{" "}
              {transaction.asset}
            </p>

            <p>
              <strong>Amount:</strong>{" "}
              {transaction.amount} CRC
            </p>

            <p>
              <strong>Tenor:</strong>{" "}
              {transaction.tenor}
            </p>

            <p>
              <strong>Status:</strong>{" "}
              {transaction.status}
            </p>

            <p>
              <strong>Block:</strong>{" "}
              {transaction.blockNumber ||
                "Pending"}
            </p>

          </section>
        )}

      </section>

    </main>
  );
}

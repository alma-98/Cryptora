import { useState } from "react";

import Login from "./pages/Login";
import Dashboard from "./pages/Dashboard";
import Administrator from "./pages/Administrator";
import Coin from "./pages/Coin";
import Wallet from "./pages/Wallet";
import Transaction from "./pages/Transaction";
import Tenor from "./pages/Tenor";
import NativeDashboard from "./pages/NativeDashboard";

type Page =
  | "dashboard"
  | "native"
  | "coin"
  | "wallet"
  | "transaction"
  | "tenor"
  | "administrator";

export default function App() {

  const [authenticated, setAuthenticated] =
    useState(false);

  const [page, setPage] =
    useState<Page>("dashboard");

  if (!authenticated) {
    return (
      <Login
        onLogin={() =>
          setAuthenticated(true)
        }
      />
    );
  }

  const renderPage = () => {

    switch (page) {

      case "dashboard":
        return <Dashboard />;

      case "native":
        return <NativeDashboard />;

      case "coin":
        return <Coin />;

      case "wallet":
        return <Wallet />;

      case "transaction":
        return <Transaction />;

      case "tenor":
        return <Tenor />;

      case "administrator":
        return <Administrator />;

      default:
        return <Dashboard />;
    }
  };

  return (
    <div
      style={{
        minHeight: "100vh",
        display: "flex",
        background: "#f8fafc"
      }}
    >
      <aside
        style={{
          width: "250px",
          minHeight: "100vh",
          background: "#0f172a",
          color: "white",
          padding: "24px 16px",
          boxSizing: "border-box",
          flexShrink: 0
        }}
      >
        <div
          style={{
            fontSize: "22px",
            fontWeight: 800
          }}
        >
          Cryptora
        </div>

        <div
          style={{
            fontSize: "12px",
            color: "#94a3b8",
            marginBottom: "28px"
          }}
        >
          Native Blockchain Wallet
        </div>

        <nav
          style={{
            display: "flex",
            flexDirection: "column",
            gap: "6px"
          }}
        >
          <NavButton
            label="Dashboard"
            onClick={() =>
              setPage("dashboard")
            }
          />

          <NavButton
            label="Native Blockchain"
            onClick={() =>
              setPage("native")
            }
          />

          <NavButton
            label="Coin"
            onClick={() =>
              setPage("coin")
            }
          />

          <NavButton
            label="Wallet"
            onClick={() =>
              setPage("wallet")
            }
          />

          <NavButton
            label="Transaction"
            onClick={() =>
              setPage("transaction")
            }
          />

          <NavButton
            label="Tenor"
            onClick={() =>
              setPage("tenor")
            }
          />

          <NavButton
            label="Administrator"
            onClick={() =>
              setPage("administrator")
            }
          />
        </nav>

        <button
          onClick={() =>
            setAuthenticated(false)
          }
          style={{
            ...buttonStyle,
            marginTop: "30px",
            background: "#7f1d1d"
          }}
        >
          Logout
        </button>
      </aside>

      <main
        style={{
          flex: 1,
          minWidth: 0
        }}
      >
        {renderPage()}
      </main>
    </div>
  );
}

function NavButton({
  label,
  onClick
}: {
  label: string;
  onClick: () => void;
}) {
  return (
    <button
      onClick={onClick}
      style={buttonStyle}
    >
      {label}
    </button>
  );
}

const buttonStyle = {
  width: "100%",
  border: 0,
  borderRadius: "8px",
  padding: "12px 14px",
  textAlign: "left" as const,
  background: "transparent",
  color: "white",
  cursor: "pointer",
  fontSize: "14px"
};

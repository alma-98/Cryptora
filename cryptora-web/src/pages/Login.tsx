interface LoginProps {
  onLogin: () => void;
}

export default function Login({ onLogin }: LoginProps) {
  return (
    <main
      style={{
        minHeight: "100vh",
        display: "grid",
        placeItems: "center",
        background: "#0f172a",
        fontFamily: "Inter, system-ui, sans-serif"
      }}
    >
      <section
        style={{
          width: "360px",
          maxWidth: "90%",
          background: "white",
          padding: "32px",
          borderRadius: "16px",
          boxSizing: "border-box"
        }}
      >
        <h1>Cryptora Wallet</h1>

        <p style={{ color: "#64748b" }}>
          Administrator Login
        </p>

        <input
          placeholder="Username"
          defaultValue="administrator"
          style={{
            width: "100%",
            padding: "12px",
            marginBottom: "12px",
            boxSizing: "border-box"
          }}
        />

        <input
          type="password"
          placeholder="Password"
          defaultValue="cryptora"
          style={{
            width: "100%",
            padding: "12px",
            marginBottom: "16px",
            boxSizing: "border-box"
          }}
        />

        <button
          onClick={onLogin}
          style={{
            width: "100%",
            padding: "13px",
            border: 0,
            borderRadius: "8px",
            background: "#2563eb",
            color: "white",
            cursor: "pointer"
          }}
        >
          Login
        </button>
      </section>
    </main>
  );
}

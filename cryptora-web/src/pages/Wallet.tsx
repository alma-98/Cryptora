export default function Wallet() {
  return (
    <section style={pageStyle}>
      <h1>Wallet</h1>

      <p style={muted}>
        Registered Cryptora wallet destinations.
      </p>

      <div style={card}>
        <strong>Wallet Management</strong>
        <p>
          Use Native Blockchain for live wallet
          registration and balance operations.
        </p>
      </div>
    </section>
  );
}

const pageStyle = {
  padding: "32px",
  fontFamily: "Inter, system-ui, sans-serif"
};

const muted = {
  color: "#64748b"
};

const card = {
  marginTop: "20px",
  background: "white",
  padding: "24px",
  borderRadius: "14px",
  border: "1px solid #e2e8f0"
};

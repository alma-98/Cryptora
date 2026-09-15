export default function Coin() {
  return (
    <section style={pageStyle}>
      <h1>Native Coin</h1>

      <p style={muted}>
        Cryptora native asset management.
      </p>

      <div style={card}>
        <strong>CRC</strong>
        <p>Cryptora Coin</p>
        <p>Total Supply: 21,000,000 CRC</p>
        <p>Status: ACTIVE</p>
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

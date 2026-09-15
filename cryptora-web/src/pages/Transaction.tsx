export default function Transaction() {
  return (
    <section style={pageStyle}>
      <h1>Transaction</h1>

      <p style={muted}>
        Cryptora CRC native transactions.
      </p>

      <div style={card}>
        <strong>Transaction Engine</strong>
        <p>
          Native CRC transactions are processed by
          the Cryptora blockchain node.
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

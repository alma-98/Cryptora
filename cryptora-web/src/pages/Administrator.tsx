export default function Administrator() {
  return (
    <section style={pageStyle}>
      <h1>Administrator</h1>
      <p style={muted}>
        Administrator management.
      </p>

      <div style={card}>
        <strong>Administrator Status</strong>
        <p>ACTIVE</p>
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
